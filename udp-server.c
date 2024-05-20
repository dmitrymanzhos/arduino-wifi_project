// принимает UDP пакеты и записывает в файл

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uv.h"
#include "functions.h"

// int app(char* command){
    
//     // while (1){
//     //     // char *command = malloc(1024);
//     //     // // if (scanf("%s", command) && check_command(command) == 1) handle_command(command);
//     //     // // if(fgets(command, 1024, stdin) && check_command(command) == 1) handle_command(command, 0);
//     //     // if(fgets(command, 1024, stdin)) 
        
//         handle_command(command, "new.txt", 0);
//         // printf("%s", command);
//     // }
//     // free(command);
//     return 0;
// }

// int write(char *filename, char *time, float field_value){
//     FILE* fp = fopen(filename, "w");
//     fprintf(fp, "%s, %f\n", time, field_value);
//     fclose(fp);
//     return 0;
// }


#define CHECK(r, msg)                                       \
    if (r<0) {                                              \
        fprintf(stderr, "%s: %s\n", msg, uv_strerror(r));   \
        exit(1);                                            \
    }
  
static uv_loop_t *uv_loop;
static uv_udp_t   server;


static void on_recv(uv_udp_t* handle, ssize_t nread, const uv_buf_t* rcvbuf, const struct sockaddr* addr, unsigned flags) {
    if (nread > 0) {
        printf("%lu\n",nread);
        printf("%s",rcvbuf->base);
        printf("\n%s\n", rcvbuf->base);

        // char* data = malloc(1024);
        char* data = rcvbuf->base;
        handle_command(data, "new.txt", 0);
        // free(data);

        // char* filename = "new.txt";

        // handle_command(data, filename, 0);
        // FILE* fp = fopen("new.txt", "a");
        // fprintf(fp, "%s\n", data);
        // fclose(fp);
    }
    printf("free  :%lu %p\n",rcvbuf->len,rcvbuf->base);
    free(rcvbuf->base);
}
 
static void on_alloc(uv_handle_t* client, size_t suggested_size, uv_buf_t* buf) {
    buf->base = malloc(suggested_size);
    buf->len = suggested_size;
    printf("malloc:%lu %p\n",buf->len,buf->base);

}

int main(int argc,char *argv[]) {
    // 

    int status;
    struct sockaddr_in addr;
    uv_loop = uv_default_loop();
    

    status = uv_udp_init(uv_loop, &server);
    CHECK(status, "init");
    
create_db_file("new.txt", "volts");

    uv_ip4_addr("192.168.43.214", 7000, &addr); // what address?


    status = uv_udp_bind(&server, (const struct sockaddr*)&addr,0);
    CHECK(status,"bind");
    
    status = uv_udp_recv_start(&server, on_alloc, on_recv);
    CHECK(status,"recv");
    
    uv_run(uv_loop, UV_RUN_DEFAULT);
    
    return 0;
}