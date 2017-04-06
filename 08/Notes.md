服务端 : 收FIN，发ACK，CLOSE_WAIT
客户端 : 发FIN，收ACK，FIN_WAIT2 ===> 收FIN，发ACK TIME_WAIT

int on = 1;
if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)) < 0)
{
ERR_EXIT("setsockopt");
}