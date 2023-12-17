#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int main()
{
    int serversocket, clientsocket, bindstatus;
    char servermessage[256];
    struct sockaddr_in serveraddress, clientaddress;
    int client_address_len = sizeof(clientaddress);

    serversocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serversocket < 0)
    {
        printf("socket failed\n");
        return -1;
    }

    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_addr.s_addr = INADDR_ANY;

    bindstatus = bind(serversocket, (const struct sockaddr *)&serveraddress, sizeof(serveraddress));
    if (bindstatus < 0)
    {
        printf("binding failed\n");
        return -1;
    }
    else
    {
        printf("binding is successful\n");
    }

    listen(serversocket, 3);
    printf("Waiting for client connection...\n");

    clientsocket = accept(serversocket, (struct sockaddr *)&clientaddress, (socklen_t *)&client_address_len);
    if (clientsocket < 0)
    {
        printf("connection is rejected by server\n");
        return -1;
    }
    else
    {
        printf("connection is accepted\n");
    }

    int data_size, framelength_bits;
    int data[data_size];
    int length_databits[framelength_bits];
    bool flag = true;

    recv(clientsocket, &data_size, sizeof(data_size), 0);
    recv(clientsocket, &length_databits, sizeof(length_databits), 0);
    recv(clientsocket, &framelength_bits, sizeof(framelength_bits), 0);

    for(int i = 0; i < data_size; i++)
     {   recv(clientsocket, &data[i], sizeof(data[i]), 0);
        printf("%d ", data[i]);}
        printf("\n");

    for(int i = 0; i < framelength_bits; i++)
      {  recv(clientsocket, &length_databits[i], sizeof(length_databits[i]), 0);
        printf("%d ", length_databits[i]);}
        printf("\n");

    framelength_bits = 0;

    for(int i = 0; i < data_size; )
    {
        if(data[i] == length_databits[framelength_bits])
        {
            i = i + data[i];
            framelength_bits++;
        }
        else
        {
            flag = false;
            break;
        }
    }

    if(flag)
        printf("\nThe data received is correct\n");
    else
        printf("\nThe data received is incorrect\n");


    close(serversocket);
    return 0;
}