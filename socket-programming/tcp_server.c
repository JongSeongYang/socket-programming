#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#define MAX 128
#define PORT 16642
#define PENDING 10
#define CLIENT_SIZE 5

int DATA_SEND_RECV(int);

int main(int argc, char* argv[])
{
	int sock_flag, conn_flag, length;
	struct sockaddr_in server_addr, client_addr;

	if ((sock_flag = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		printf("Socket ���� ����...\n");
		exit(0);
	}
	else
		printf("Socket ���� ����...\n");
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);

	if ((bind(sock_flag, (struct sockaddr*)&server_addr, sizeof(server_addr))) != 0) {
		\
			printf("���Ϲ��ε� ����...\n");
		exit(0);
	}
	else printf("���� ���ε� ����...\n");

	if ((listen(sock_flag, CLIENT_SIZE)) != 0) {
		printf("������ ����...\n");
		exit(0);
	}
	length = sizeof(client_addr);

	if ((conn_flag = accept(sock_flag, (struct sockaddr*)&client_addr, &length)) < 0) {
		printf("����-Ŭ���̾�Ʈ ���� ����\n");
		exit(0);
	}
	else printf("����-Ŭ���̾�Ʈ ���� ����\n");
	DATA_SEND_RECV(conn_flag);
	close(sock_flag);
}

int DATA_SEND_RECV(int conn_flag)
{
	char buf[MAX];
	int idx;

	while (1) {
		memset(buf, 0x00, MAX);
		read(conn_flag, buf, sizeof(buf));
		printf("From client: %s\nTO client: ", buf);
		memset(buf, 0x00, MAX);
		fgets(buf, MAX, stdin);

		write(conn_flag, buf, sizeof(buf));

		if (strncmp("exit", buf, 4) == 0) {
			printf("�������� ...\n");
			break;
		}
	}
}
