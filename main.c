#include "main.h"


onion* server = NULL;

int main(int argc, char** argv){
    

    signal(SIGINT, shutdown_server);
    signal(SIGTERM, shutdown_server);

   //ONION_VERSION_IS_COMPATIBLE_OR_ABORT();
    server = onion_new(O_POLL); 
    onion_url* urls = init_url(server);

    onion_listen(server);
    onion_free(server);
    return 1;
}

void shutdown_server(int _) {
  if (server)
    onion_listen_stop(server);
}

onion_url* init_url(onion* server){
    onion_set_hostname(server, "0.0.0.0");
    onion_url* urls = onion_root_url(server);

    onion_url_add(urls, "", index_view);
    onion_url_add(urls, "hello", hello_view);
    onion_url_add(urls, "page", page_view);
    return urls;
}