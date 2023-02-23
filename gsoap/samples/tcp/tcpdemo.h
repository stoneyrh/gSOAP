
//gsoap ns service name: tcpdemo
//gsoap ns service namespace: urn:tcpdemo

struct ns__ClientData
{
  @int id;
  const char *client_message;
};

struct ns__ServerData
{
  @int id;
  const char *server_message;
};

int ns__echo(struct ns__ClientData*, struct ns__ServerData*);
int ns__more(struct ns__ClientData*, void);
int ns__data(struct ns__ServerData*, void);
int ns__bye(void);
