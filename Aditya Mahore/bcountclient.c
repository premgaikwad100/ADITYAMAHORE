#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int i, j;

int main()
{
    int clientsocket;
    struct sockaddr_in serveraddress;
    int connection_status;

    clientsocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientsocket < 0)
    {
        printf("socket creation failed\n");
        return -1;
    }

    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_addr.s_addr = INADDR_ANY;

    connection_status = connect(clientsocket, (struct sockaddr *)&serveraddress, sizeof(serveraddress));
    if (connection_status == -1)
    {
        printf("connection failed\n");
        return -1;
    }

    int data_size, framelength_bits = 0;
    printf("Enter the total size of the input data: ");
    scanf("%d", &data_size);

    int data[data_size];
    printf("Enter the data: ");
    for(i = 0; i < data_size; i++)
        scanf("%d", &data[i]);

    int length_databits[data_size];
    for(i = 0; i < data_size; )
    {
        length_databits[framelength_bits] = data[i];
        i = i + data[i];
        framelength_bits++;
    }

    printf("Data to be transmitted is: \n");
    for(i = 0; i < data_size; i++)
        printf("%d ", data[i]);

    send(clientsocket, &data_size, sizeof(data_size), 0);
    //send(clientsocket, &data, sizeof(data), 0);
    //send(clientsocket, &length_databits, sizeof(length_databits), 0);
    send(clientsocket, &framelength_bits, sizeof(framelength_bits), 0);

    for(int i = 0; i < data_size; i++)
       send(clientsocket, &data[i], sizeof(data[i]), 0);
        

    for(int i = 0; i < framelength_bits; i++)
        send(clientsocket, &length_databits[i], sizeof(length_databits[i]), 0);


    close(clientsocket);
    return 0;
}