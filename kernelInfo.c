#include <stdio.h>
#include <string.h>

int main()
{
        FILE *fp;
        char buff[255];
        int i = 1;

        //Read from file /proc/cpuinfo
        fp = fopen("/proc/cpuinfo", "r");

        //Parse out Vendor_ID and Model Name
        while (1) 
        {
                if (fgets(buff, 255, fp) == NULL) break;

                if(strncmp(buff, "model name", 8) == 0)
                {
                        printf("%s\n", buff);
                }
                if(strncmp(buff, "vendor_id", 8) == 0)
                {
                        printf("Processor #%d:\n%s\n", i, buff);
                        i++; 
                }
        }

        fclose(fp);
       
        //Read from file /proc/version/

        fp = fopen("/proc/version", "r");

        //Display results
        fgets(buff, 255, fp);

        printf("Version: %s\n", buff);
}
