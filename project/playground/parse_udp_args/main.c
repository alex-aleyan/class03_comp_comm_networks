/* 
 *
 * Citing Sources: 
 *
 * https://www.linuxtopia.org/online_books/programming_books/gnu_c_programming_tutorial/argp-example.html 
 * 
 */

#include <stdio.h>
#include "parse_args.h"
#include <arpa/inet.h>  //inet_aton
#include <netinet/in.h> //sockaddr_in

int main (int argc, char **argv)
{
  struct arguments arguments;
  FILE *outstream;
  char waters[] = "VERBOSEVERBOSEVERBOSEVERBOSE \n";

  /* Set argument defaults */
  arguments.outfile = NULL;
  arguments.source_ip = "";
  arguments.dest_ip = "";
  arguments.source_port = "";
  arguments.dest_port = "";
  arguments.verbose = 0;

  /* Where the magic happens */
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  /* Where do we send output? */
  if (arguments.outfile) outstream = fopen (arguments.outfile, "w");
  else                   outstream = stdout;

  /* Print argument values */
  fprintf (outstream, "\n");
  fprintf (outstream, "source-ip:   %s\n",   arguments.source_ip);
  fprintf (outstream, "source-port: %s\n\n", arguments.source_port);
  fprintf (outstream, "dest-ip:     %s\n",   arguments.dest_ip);
  fprintf (outstream, "dest-port:   %s\n\n", arguments.dest_port);
  fprintf (outstream, "ARG1 = %s\n",         arguments.args[0]);
  fprintf (outstream, "ARG2 = %s\n\n",       arguments.args[1]);

  /* If in verbose mode, print song stanza */
  if (arguments.verbose) fprintf (outstream, waters);

  struct sockaddr_in adr_inet;

  if ( !inet_aton(arguments.source_ip, &adr_inet.sin_addr) )  puts ("BAD ADDRESS");
  fprintf(outstream, "The arguments.source_ip=%s\n",   arguments.source_ip);
  fprintf(outstream, "The arguments.source_ip=0x%08x\n\n", adr_inet.sin_addr);

  fprintf(outstream, "The arguments.source_port=%d\n", atoi(arguments.source_port) );
	 fprintf(outstream, "The arguments.source_port=0x%04x\n\n", htons(atoi(arguments.source_port)) );


  if ( !inet_aton(arguments.dest_ip, &adr_inet.sin_addr) )  puts ("BAD ADDRESS");
  fprintf(outstream, "The arguments.dest_ip=%s\n",   arguments.dest_ip);
  fprintf(outstream, "The arguments.dest_ip=0x%08x\n\n", adr_inet.sin_addr);

  fprintf(outstream, "The arguments.dest_port=%d\n", atoi(arguments.dest_port) );
	 fprintf(outstream, "The arguments.dest_port=0x%04x\n", htons(atoi(arguments.dest_port)) );

  return 0;
}
