#define TCP_IP				"192.168.10.10"
#define TCP_PORT			5100

#define SOCK_BUF_SIZE		128

/* USER CODE BEGIN Header_Task_ETHER_Process */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_ETHER_Process */
void Task_ETHER_Process(void const * argument)
{
  /* USER CODE BEGIN Task_ETHER_Process */

	struct sockaddr_in dest_addr;
	struct sockaddr_in src_addr; // Large enough for both IPv4 or IPv6
	uint32_t addr_len = sizeof(src_addr);
	int opt = 1;
	int listen_sock, sock;
	int err;
	uint32_t rcvBytes;
	uint8_t  rcvBuf[SOCK_BUF_SIZE];

	dest_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(TCP_PORT);

	// create socket
	listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (listen_sock < 0)
	{
		// Error : Unable to create socket : errno %d,
		vTaskDelete(NULL);

		return;
	}

  setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  err = bind(listen_sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
  if (err != 0)
  {
  	// Error : Socket unable to bind : errno %d

  	goto CLEAN_UP;
  }

  err = listen(listen_sock, 1);	///TCP_DEFAULT_LISTEN_BACKLOG
  if (err != 0)
  {
  	// Error : Socket unable to bind : errno %d

  	goto CLEAN_UP;
  }


  /* Infinite loop */
  for(;;)
  {

  	sock = accept(listen_sock, (struct sockaddr *)&src_addr, &addr_len);

  	if (sock > 0)
  	{
  		do
  		{

				rcvBytes = recv(sock, rcvBuf, SOCK_BUF_SIZE, MSG_MORE);

				if (rcvBytes != 0)
				{

				}
  		} while (rcvBytes != 0);

  		close(sock);

  	} // socket
//
//  	shutdown(sock, 0);
//  	close(sock);
  }

CLEAN_UP:
		close(listen_sock);
		vTaskDelete(NULL);

  /* USER CODE END Task_ETHER_Process */
}
