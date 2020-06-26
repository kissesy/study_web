#include <onion/onion.h>
#include <onion/log.h>
#include <signal.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include "ctemplate.h"


void shutdown_server(int _);
onion_url* init_url(onion* server);


/* View */
int index_view(void* p, onion_request* req, onion_response* res);
int hello_view(void* p, onion_request* req, onion_response* res);
int page_view(void* p, onion_request* req, onion_response* res);

char* MakeTemplateBuffer(TMPL_varlist* context, const char* temaplate_path);

void shutdown_server(int _);