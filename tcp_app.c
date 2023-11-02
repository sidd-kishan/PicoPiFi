#include "lwip/init.h"
#include "lwip/timeouts.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/netif.h"
#include "lwip/ip4_addr.h"
#include "lwip/sockets.h"
#include "lwip/apps/lwiperf.h"
#include "wifi_code.h"
char ssid[32],key[32];
int tcp_app()
{
  int i;
  int s;
  int c;
  int port = 2542;
  struct sockaddr_in address;
  s = lwip_socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0)
  {
    perror("socket");
    return 1;
  }
  i = 1;
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &i, sizeof i);
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
  address.sin_family = AF_INET;
  if (bind(s, (struct sockaddr *)&address, sizeof(address)) < 0)
  {
    perror("bind");
    return 1;
  }
  //printf("%s,%d\n", __func__, __LINE__);
  if (listen(s, 1) < 0)
  {
    perror("listen");
    return 1;
  }

  fd_set conn;
  int maxfd = 0;
  FD_ZERO(&conn);
  FD_SET(s, &conn);
  maxfd = s;
  //printf("%s,%d\n", __func__, __LINE__);
  while (1)
  {
    fd_set read = conn, except = conn;
    int fd;
    if (select(maxfd + 1, &read, 0, &except, 0) < 0)
    {
      perror("select");
      break;
    }
    for (fd = 0; fd <= maxfd; ++fd)
    {
      if (FD_ISSET(fd, &read))
      {
        if (fd == s)
        {
          int newfd;
          socklen_t nsize = sizeof(address);

          newfd = accept(s, (struct sockaddr *)&address, &nsize);

          //               if (verbose)
          //printf("connection accepted - fd %d\n", newfd);
          if (newfd < 0)
          {
            perror("accept");
          }
          else
          {
            //printf("setting TCP_NODELAY to 1\n");
            int flag = 1;
            int optResult = setsockopt(newfd,
                                       IPPROTO_TCP,
                                       TCP_NODELAY,
                                       (char *)&flag,
                                       sizeof(int));
            if (optResult < 0)
              perror("TCP_NODELAY error");
            if (newfd > maxfd)
            {
              maxfd = newfd;
            }
            FD_SET(newfd, &conn);
          }
        }
        else if (handle_data(fd, NULL))
        {
          close(fd);
          FD_CLR(fd, &conn);
        }
      }
      else if (FD_ISSET(fd, &except))
      {
        close(fd);
        FD_CLR(fd, &conn);
        if (fd == s)
          break;
      }
    }
  }
  return 0;
}


int handle_data(int fd, fd_set *conn) {
    char buffer[1024];
    ssize_t bytes_received, bytes_sent;

    // Receive data from the client
    bytes_received = recv(fd, buffer, sizeof(buffer), 0);
    if (bytes_received <= 0) {
        return 1; // Close the connection
    } else {
        // Check if the received data is "getinfo"
        if (strncmp(buffer, "getinfo", 7) == 0) {
			//xSemaphoreTake(wifi_scan_info_mutex, portMAX_DELAY);
            // Copy the value of scan_results to the buffer
			memcpy(buffer, scan_results, strlen(scan_results));
			buffer[strlen(scan_results)] = '\0';
			//xSemaphoreGive(wifi_scan_info_mutex);
			
			// Send back the modified data (echo or scan_results)
			bytes_sent = send(fd, buffer, strlen(buffer), 0);
        } else if (strncmp(buffer, "setwifi", 7) == 0) {
            // Extract ssid and key from the input buffer
            char *ptr = buffer + 8; // Skip "setwifi "
            int ssid_len = 0, key_len = 0;
            while (*ptr != '\0') {
                if (strncmp(ptr, "ssid:", 5) == 0) {
                    ptr += 5; // Skip "ssid:"
                    ssid_len = strcspn(ptr, " ");
                    memcpy(ssid, ptr, ssid_len);
                    //ssid[ssid_len] = '\0'; // Ensure null-terminated string
                    ptr += ssid_len; // Move past the ssid
                } else if (strncmp(ptr, "key:", 4) == 0) {
                    ptr += 4; // Skip "key:"
                    key_len = strcspn(ptr, "\r\n");
                    memcpy(key, ptr, key_len);
                    //key[key_len] = '\0'; // Ensure null-terminated string
                    ptr += key_len; // Move past the key
                } else {
                    // Move to the next token if not ssid or key
                    ptr += strcspn(ptr, " \r\n") + 1;
                }
            }
        } else if (strncmp(buffer, "getcred", 7) == 0) {
            // Prepare the response with ssid and key details
            //char response[100];
            snprintf(buffer, sizeof(buffer), "ssid:%s key:%s \r\n\0", ssid, key);

            // Send back the response to the client
            bytes_sent = send(fd, buffer, strlen(buffer), 0);
        } else if (strncmp(buffer, "diswifi", 7) == 0) {
            //xSemaphoreTake(wifi_connection_set, portMAX_DELAY);
			//wifi_scanning_switched_on=true;
			//xSemaphoreGive(wifi_connection_set);
        }

        // Clear the buffer after it is sent
        memset(buffer, 0, sizeof(buffer));
    }

    return 0; // Continue the connection
}