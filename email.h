#include <curl/curl.h>

FILE *logfile;

char payload_txt[10000];

struct upload_status {
  int lines_read;
};
 
static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
  static const char *payload_text[] = {payload_txt};

  struct upload_status *upload_ctx = (struct upload_status *)userp;
  const char *data;
 
  if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
    return 0;
  }
 
  data = payload_text[upload_ctx->lines_read];
 
  if(data) {
    size_t len = strlen(data);
    memcpy(ptr, data, len);
    upload_ctx->lines_read++;
 
    return len;
  }
 
  return 0;
}
 
int send_Mail_Gmail_cURL_Engine(char FROM[], char TO[],char USERNAME[], char PASSWORD[], char DATA[])
{
  for (int i=0;i<strlen(DATA);i++)
    payload_txt[i]=DATA[i];

  CURL *curl;
  CURLcode res = CURLE_OK;
  struct curl_slist *recipients = NULL;
  struct upload_status upload_ctx;
 
  upload_ctx.lines_read = 0;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_USERNAME, USERNAME);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, PASSWORD);
    curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");
    curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_CAINFO, "google.pem");
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM);
    recipients = curl_slist_append(recipients, TO);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
    curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
 
    res = curl_easy_perform(curl);

    if(res != CURLE_OK)
    {
      logfile=fopen("Data/logs.data","a");
      time_t t;
      time(&t);
      cout<<endl<<"Some error occured while sending mail to "<<TO<<"..."<<endl;
      cout<<"Check your internet connection..."<<endl;
      cout<<"Check log file for further info..."<<endl;
      fprintf(logfile, "%s%s\n%s\n\n", ctime(&t), TO, curl_easy_strerror(res));
      fclose(logfile);
    }
 
    curl_slist_free_all(recipients);
 
    curl_easy_cleanup(curl);
  }
  return (int)res;
}
