#include "main.h"


//onion_connection_status

int index_view(void* p, onion_request* req, onion_response* res){

    char* buffer = MakeTemplateBuffer(NULL, "template/index.html");
    if(buffer == NULL){
        ONION_INFO("MakeTemplateBuffer Function return NULL");
        onion_response_write0(res, "Hmm Iternal Error....");
        return OCS_PROCESSED;
    }
    onion_response_printf(res, "%s", buffer);
    free(buffer);
    return OCS_PROCESSED;
}

/*
if (onion_request_get_flags(req) & OR_POST)

method 체크랑 otemplate 사용하기
onion_request_get_flags (onion_request *req)
enum  	onion_request_flags_e {
  OR_METHODS = 0x0F, OR_GET = 0, OR_POST = 1, OR_HEAD = 2,
  OR_OPTIONS = 3, OR_PROPFIND = 4, OR_PUT = 5, OR_DELETE = 6,
  OR_MOVE = 7, OR_MKCOL = 8, OR_PROPPATCH = 9, OR_PATCH = 10,
  OR_HTTP11 = 0x10, OR_POST_MULTIPART = 0x20, OR_POST_URLENCODED = 0x40, OR_NO_KEEP_ALIVE = 0x0100,
  OR_HEADER_SENT_ = 0x0200, OR_INTERNAL_ERROR = 0x01000, OR_NOT_IMPLEMENTED = 0x02000, OR_NOT_FOUND = 0x03000,
  OR_FORBIDDEN = 0x04000
}
*/
int hello_view(void* p, onion_request* req, onion_response* res){

    if(!(onion_request_get_query(req, "firstname") != NULL) 
    || !(onion_request_get_query(req, "lastname") != NULL) ){
        onion_response_printf(res, "please fill blank...");
        return OCS_PROCESSED;
    }
    onion_response_write0(res, "Hello WORLD onion!");
    const char* firstname = onion_request_get_query(req, "firstname");
    const char* lastname = onion_request_get_query(req, "lastname");

    onion_response_printf(res, "<p>firstname : %s<p>lastname : %s", firstname, lastname);
    return OCS_PROCESSED;
}

int page_view(void* p, onion_request* req, onion_response* res){ 

    TMPL_varlist* context; 
    context = TMPL_add_var(0, "title", "Hello WOrld!", 0);
    context = TMPL_add_var(context, "variable", "This Page is Template Language!", 0);
    char* buffer = MakeTemplateBuffer(context, "template/page.html");
    if(buffer == NULL){
        ONION_INFO("MakeTemplateBuffer Function return NULL");
        onion_response_write0(res, "Hmm Iternal Error....");
        return OCS_PROCESSED;
    }
    onion_response_printf(res, "%s", buffer);
    free(buffer);
	TMPL_free_varlist(context);
    return OCS_PROCESSED;
}

char* MakeTemplateBuffer(TMPL_varlist* context, const char* template_path){
    char* buffer;
    size_t size;
    FILE* out = open_memstream(&buffer, &size);
    if(out == NULL){
        return NULL;
    }

    TMPL_write(template_path, 0, 0, context, out, stderr);
    fclose(out);
    return buffer;
}
