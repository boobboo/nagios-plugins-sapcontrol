const char *progname = "check_sapcontrol";
const char *copyright = "2013";
const char *email = "dlittle@toyatech.net";

#include "common.h"
#include "utils.h"
#include <ctype.h>

#include "SAPControlH.h"
#include "SAPControl.nsmap"

#define DEFAULT_HOSTNAME "localhost"
#define DEFAULT_URL "http://localhost:50013/SAPControl.cgi"
#define DEFAULT_SYSNR 0
#define DEFAULT_FUNCTION "GetProcessList"

struct timeval tv;

int timeout;
char *critical_thresholds;
char *warning_thresholds;
char *hostname;
char *url;
long sysnr = -1;
char *function;

int process_arguments(int, char **);
int check_sapcontrol(void);
int check_sapcontrol_getprocesslist(struct soap *);
int print_help(void);
int print_usage(void);

int 
main (int argc, char **argv) 
{
  int result = STATE_UNKNOWN;

  //setlocale (LC_ALL, "");
  //bindtextdomain (PACKAGE, LOCALEDIR);
  //textdomain (PACKAGE);

  url = strdup(DEFAULT_URL);

  if (process_arguments (argc, argv) == ERROR)
    usage4 (_("Could not parse arguments\n"));

  /* initialize alarm signal handling, set socket timeout, start timer */
  (void) alarm (timeout);
  gettimeofday (&tv, NULL);

  result = check_sapcontrol();
  return result;
}

/* process command-line arguments */
int 
process_arguments (int argc, char **argv) 
{

  int c = 1;
  
  int option = 0;
  static struct option longopts[] = {
    {"version", no_argument, 0, 'V'},
    {"verbose", no_argument, 0, 'v'},
    {"help", no_argument, 0, 'h'},
    {"timeout", required_argument, 0, 't'},
    {"critical", required_argument, 0, 'c'},
    {"warning", required_argument, 0, 'w'},
    {"hostname", required_argument, 0, 'H'},
    {"sysnr", required_argument, 0, 'N'},
    {"function", required_argument, 0, 'F'},
    {0, 0, 0, 0}
  };

  while (1) {
    c = getopt_long (argc, argv, "Vvht:c:w:H:N:F:", longopts, &option);
    if (c == -1 || c == EOF)
      break;

    switch (c) {
      case '?': /* usage */
        usage5 ();
        break;
      case 'h': /* help */
        print_help();
        exit (STATE_OK);
        break;
      case 'V': /* version */
        print_revision(progname, VERSION);
        exit (STATE_OK);
        break;
      case 't': /* timeout */
        if (!is_intnonneg (optarg))
          usage2 (_("Timeout interval must be a positive integer"), optarg);
        else
          timeout = atoi (optarg);
        break;
      case 'c': /* critical */
        critical_thresholds = optarg;
        break;
      case 'w': /* warning */
        warning_thresholds = optarg;
        break;
      case 'H': /* hostname */
        hostname = optarg;
        break;
      case 'N': /* sysnr */
        sysnr = strtol(optarg, NULL, 10);
        break;
      case 'F': /* function */
        function = optarg;
        break;
    }
  }

  if (hostname == NULL)
    hostname = DEFAULT_HOSTNAME;
  if (sysnr == -1)
    sysnr = DEFAULT_SYSNR;
  if (function == NULL)
    function = DEFAULT_FUNCTION;

  return TRUE;
}

int 
check_sapcontrol(void) 
{
  struct soap *soap = soap_new();
  soap_end(soap);
  return STATE_UNKNOWN;
}

int check_sapcontrol_getprocesslist(struct soap *soap) {
  struct _ns1__GetProcessList function;
  struct _ns1__GetProcessListResponse result;
  if (soap_call___ns1__GetProcessList(soap, url, "GetProcessList", &function, &result) == SOAP_OK) {
    struct ns1__ArrayOfOSProcess *aop = result.process;
    struct ns1__OSProcess* items = aop->item;
    int i;
    for (i = 0; i < aop->__sizeitem; i++) {
      //implement something
    }
  } else {
    char *error;
    char *message = "CHECK_SAPCONTROL CRITICAL - SOAP Error: ";
    char buf[4096 - sizeof(message)];
    soap_sprint_fault(soap, &error, sizeof(buf));
    
  } 
}

int print_usage() {
  printf("check_sapcontrol -H <hostname> -N <sysnr> -F <function>\n");
  exit (STATE_OK);
}

int print_help() {
  printf("check_sapcontrol\n\t--hostname,-H\tHostname of SAP server.\n\t--sysnr,-N\tSAP system or instance number (00 to 98)\n\t--function,-F\tFunction to check.\n");
}

