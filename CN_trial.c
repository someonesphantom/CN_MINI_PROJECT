#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <math.h>
#define      _GNU_SOURCE
#define BASE 2  

int ping(char *ipaddr) 
{
  char *command = NULL;
  FILE *fp;
  int stat = 0;
  asprintf (&command, "%s %s -q 2>&1", "fping", ipaddr);
  fp = popen(command, "r");
  if (fp == NULL) {
    fprintf(stderr, "Failed to execute fping command\n");
    free(command);
    return -1;
  }
  stat = pclose(fp);
  free(command);
  return WEXITSTATUS(stat);
}

/*  Check if an ip address is valid */
int isValidIpAddress(char *ipaddr)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ipaddr, &(sa.sin_addr));
    return result != 0;
}

// Function to find out the Class
char findClass(char str[])
{
   // storing first octet in arr[] variable
   char arr[4];
   int i = 0;
   while (str[i] != '.')
   {
      arr[i] = str[i];
      i++;
   }
   i--;

   // converting str[] variable into number for
   // comparison
   int ip = 0, j = 1;
   while (i >= 0)
   {
      ip = ip + (str[i] - '0') * j;
      j = j * 10;
      i--;
   }

   // Class A
   if (ip >=1 && ip <= 126)
      return 'A';

   // Class B
   else if (ip >= 128 && ip <= 191)
      return 'B';

   // Class C
   else if (ip >= 192 && ip <= 223)
      return 'C';

   // Class D
   else if (ip >= 224 && ip <= 239)
      return 'D';

   // Class E
   else
      return 'E';
}


int binaryTodecimal( int bin_num)  
{  
    // declaration of variables  
    int decimal_num = 0, temp = 0, rem;  
    while (bin_num != 0)  
    {  
        rem = bin_num % 10;  
        bin_num = bin_num / 10;  
        decimal_num = decimal_num + rem * pow( 2, temp);  
        temp++;  
    }  
    return decimal_num;  
}  
long tobinary(int dec){
   long bin=0,rem,f=1;
   while(dec != 0){
      rem = dec % 2;
      bin = bin + rem * f;
      f = f * 10;
      dec = dec / 2;
   }
   return bin;
}
// void networks(double numNet,uint32_t  ip_address, int CIDR, uint32_t networkID){

//   unsigned long hoststart;
//   unsigned long hostend;
//   hoststart = 1;
//   hostend = (1 << (32 - CIDR)) - 1;

//   // Calculate all host addresses in the range
//   for (unsigned i = hoststart; i <= hostend; i++) {
//     uint32_t hostip;
//     int b1, b2, b3, b4;
//     char ipstr[16];

//     hostip = networkID + hoststart;
//     b1 = (hostip & 0xff000000) >> 24;
//     b2 = (hostip & 0x00ff0000) >> 16;
//     b3 = (hostip & 0x0000ff00) >> 8;
//     b4 = (hostip & 0x000000ff);
//     snprintf(ipstr, sizeof(ipstr), "%d.%d.%d.%d", b1, b2, b3, b4);
//     printf("%s\n", ipstr);
//     numNet--;
//   }
// }

void ipAddress_LF(char *host_ip, int CIDR)
{
   char subnet[200],temp[1000],subnetmask[200],temp1[1000];
    int num=0,dec=0,i =0,j=0,k=0;
   for(i = 0;i < 35;i++){
      if(i==8||i==17||i==26){
         subnet[i] = '.';
      }
      else if(i < CIDR+3){
         subnet[i]='1';
      }
      else{
         subnet[i]='0';
      }
   }
   printf("%s\n",subnet);

  for(int l=0;l<0;l++){
      temp[j]=subnet[i];
      if(subnet[i]=='.'){
         num = atoi(temp);
         dec  = binaryTodecimal(num);
         sprintf(temp1,"%d",dec);
         strcat(subnetmask,temp1);
         strcat(subnetmask,".");
         printf("hi %s\n",subnetmask );
         k++;
         num=0;
         dec=0;
         j=0;
      }
      if(k==2){
        num = atoi(temp);
        dec  = binaryTodecimal(num);
        //change to string from number
        sprintf(temp1,"%d",dec);
        strcat(subnetmask,temp1);
        printf("%s\n",subnetmask );
        num=0;
        dec=0;
        j=0;
      }
      else if(subnet[i] == '\0')
        break;
      i++;
      j++;

   }
   printf("hi %s\n",subnetmask );
   char *netmask = subnetmask ;
   //inet_ntop(AF_INET,&);
   struct in_addr host, mask, broadcast, network,next_network,next_broadcast;
   char broadcast_address[INET_ADDRSTRLEN];
   char network_address[INET_ADDRSTRLEN];
   char next_network_address[INET_ADDRSTRLEN];
   char next_broadcast_address[INET_ADDRSTRLEN];
    if (inet_pton(AF_INET, host_ip, &host) && inet_pton(AF_INET, netmask, &mask)){
        //mask.s_addr = ~(0xFFFFFFFF >> 24);
        network.s_addr = (host.s_addr & mask.s_addr);
        broadcast.s_addr = ((host.s_addr & mask.s_addr) | ~mask.s_addr);

    }
    else {
        fprintf(stderr, "Failed converting strings to numbers\n");
    }
    if ((inet_ntop(AF_INET, &broadcast.s_addr, broadcast_address, INET_ADDRSTRLEN) != NULL) && (inet_ntop(AF_INET, &network.s_addr, network_address, INET_ADDRSTRLEN) != NULL)){
      double numAddr = (pow(2,32-CIDR));
      int numAddr_bin = tobinary(numAddr);
      printf("no.of address : %f\n",numAddr);
      printf("Broadcast address of %s is %s\n",host_ip, broadcast_address);
      printf("Network ID of %s is %s\n",host_ip, network_address);
      double numNet;
      numNet = CIDR%8;
      printf("No.of networks: %f\n",numNet);
      if(inet_pton(AF_INET, host_ip, &host) && inet_pton(AF_INET, netmask, &mask)){
        network.s_addr = (host.s_addr & mask.s_addr);
        next_broadcast.s_addr = broadcast.s_addr;
        char *stopstring; 
        uint32_t ip_address = strtoul(host_ip, &stopstring, BASE);
        uint32_t networkID = strtoul(network_address, &stopstring, BASE);
        
        //networks(numNet,ip_address,CIDR,networkID);
          // next_network.s_addr = next_broadcast.s_addr  ;
          // next_broadcast.s_addr = ((next_network.s_addr & mask.s_addr) | ~mask.s_addr) ;
          // inet_ntop(AF_INET,&next_network.s_addr,next_network_address,INET_ADDRSTRLEN);
          // printf("Network number %d has Network ID %s \n",i,next_network_address);
          // numNet--;
          // i++;
      }

      //inet_ntop(AF_INET, &broadcast.s_addr+mask.s_addr, broadcast_address, INET_ADDRSTRLEN);
      //printf("Broadcast address of %s is %s\n",host_ip, broadcast_address);
    }

}



int main() {
   char ip1[] = "72.20.10.0";
   char subnet[] = "255.255.255.192";
   //scanf("%s",ip1);
   //printf("Enter subnet");
   //scanf("%s",subnet);
   char temp[100],temp1[100];
   //char str[] = "192.226.12.11";
   char ipClass;
   int status=0;
   strcpy(temp,ip1);
   strcpy(temp1,ip1);
   if(isValidIpAddress(temp)){
      status = ping(temp1);
      if(status){
        printf("Could ping %s successfully, status %d\n", ip1, status);
     } else {
       printf("Machine not reachable, status %d\n", status);
    }
    ipAddress_LF(temp1,26);
    ipClass = findClass(ip1);
    printf("Given IP address(%s) belongs to Class %c\n",ip1,ipClass);

 } 
 else
   printf("Not valid\n");
}
