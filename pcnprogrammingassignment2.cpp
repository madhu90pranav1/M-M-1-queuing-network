#include <iostream>
#include <math.h>

using namespace std;

double seed=1111.0;
double clock1,EN1,EN2,EN3,r13,ewaitin1,ewaitin2,ewaitin3,u1,u2,r,u3,util1,util2,util3,lamda,mu1,mu2,mu3,rs1,rs2,r32,r11,r3d,N1,N2,N3,N1dep,N2dep,N3dep,Nsdep,through1,through2,through3;

double uni_rv()
{
double k=16807.0;
double m=2.147483647e9;
double rv;
seed= fmod((k*seed),m);
rv= seed/m;
return (rv);
}
double exp_rv(double lambda)
{
    double exp;
    exp = ((-1) / lambda) * log(uni_rv());
    return(exp);
}
struct event {
  double time;            // Time at which Event takes place
  int type;               // Type of Event
  event* next;            // Points to nex1;

  event(double t, int i) {
    time = t;
    type = i;
    next = 0;
  }
};

class eventList {
  event* head;           // Points to first Event in EventList
  int event_count;       // Total number of Events in EventList
public:
  ~eventList() { clear();}
  eventList() { event_count = 0; head = 0;}
  void insert(double time, int type)  // Insert new event into EventList
  {
  //cout<<endl<<"Inserting element type "<<type;
  event_count++;                        // Increment number of events in list.
  event* eptr = new event(time, type);
  if (head == 0) {                      // If EventList is empty, 
    head = eptr;                        // put new event at head of list.
    eptr->next = 0;
  }
  else if (head->time >= eptr->time) {  // If the event is earlier than
    eptr->next = head;                  // all existing events, place it
    head = eptr;                        // at the head of the list.
  }
  else {                                // Otherwise, search for the
    event* eindex;                      // correct location sorted by time. 
    eindex = head;
    while (eindex->next != 0) {
      if (eindex->next->time < eptr->time) {
        eindex = eindex->next;
      }
      else {
        break;
      }
    }
    eptr->next = eindex->next;
    eindex->next = eptr;
  }
}

  event* get()                       // Returns first Event in EventList
  {
  if (event_count == 0) {
    return 0;
  }
  else {
    event_count--;
    event* eptr;
    eptr = head;
    head = head->next;
    eptr->next = 0;
	//cout<<endl<<"Removing event type"<<eptr->type;
	//cout<<endl<<"Head :"<<head->type;
    return eptr;
  }
}

  void clear()                        // Removes all Events from EventList
  {
  event* eptr;
  while(head)
  {
    eptr = head;
    head = head->next;
    eptr->next = 0;
    delete eptr;
  }
  event_count = 0;
}
  
  event* remove(int type)            // Returns first Event of given type
{
  if (event_count == 0 || head ==0) {
    return 0;
  }
  else {
    event* eptr;
    event* eptr_prev = 0;
    eptr = head;

    while(eptr){
      if (eptr->type == type) {
        if (eptr_prev == 0) {
          head = eptr->next;
          eptr->next = 0;
          return eptr;
        }
        else {
          eptr_prev->next = eptr->next;
          eptr->next = 0;
          return eptr;
        }
      }
      else {
        eptr_prev = eptr;
        eptr = eptr->next;
      }
    }
    return 0;
  }
}
  
}elist;
void e1()
  {
  N1++;
                                        
      elist.insert(clock1+exp_rv(lamda*rs1),1); 
      if (N1==1) 
	{                             
        elist.insert(clock1+exp_rv(mu1),4);   
        }
  }
  void e2()
  {
  N2++;
                                         
      elist.insert(clock1+exp_rv(lamda*rs2),2); 
      if (N2==1) 
	{                             
        elist.insert(clock1+exp_rv(mu2),5);   
        }
	}

	void e3()
	{
	N3++;
	  if (N3==1)
	  
	{                             
        elist.insert(clock1+exp_rv(mu3),6);   
        }
		
}
void d1()
{
N1--;                                    
      N1dep++;
      r=uni_rv(); 
      if(r<=r11)
	{
	elist.insert(clock1,7);
	}
      else
	{
	elist.insert(clock1,3);
	}                            
      if (N1 > 0) 
	{                            
        elist.insert(clock1+exp_rv(mu1),4);   
	} 
}
void d2()
{
N2--;                                    
      N2dep++;
      elist.insert(clock1,3);                        
      if (N2 > 0) 
	{                            
        elist.insert(clock1+exp_rv(mu2),5);   
	} 
}
void d3()
{
N3--;                                    
      N3dep++;
      r=uni_rv(); 
      if(r<=r32)
	{
	elist.insert(clock1,8);
	}
      else
	{
 	
	Nsdep++;
	}                            
      if (N3 > 0) 
	{                            
        elist.insert(clock1+exp_rv(mu3),6);   
	} 
}
void r1()
{
N1++;                                     
      if (N1==1) 
	{                             
        elist.insert(clock1+exp_rv(mu1),4);   
        }
      
}
void r2()
{
N2++;                                     
      if (N2==1) 
	{                             
        elist.insert(clock1+exp_rv(mu2),5);   
        }
}
void practical()
{
int done=0;
event *currentevent;
elist.insert(exp_rv(lamda*rs1),1); 
  elist.insert(exp_rv(lamda*rs2),2); 

  
while(!done)
{
currentevent= elist.get();
double prev=clock1;
clock1= currentevent->time;
EN1 += N1*(clock1-prev);
    EN2 += N2*(clock1-prev);  
    EN3 += N3*(clock1-prev);
    if(N1>0)
    u1 += (1*(clock1-prev));
    else
    u1 += (0*(clock1-prev));
    if(N2>0)
    u2 += (1*(clock1-prev));
    else
    u2 += (0*(clock1-prev));
    if(N3>0)
    u3 +=(1*(clock1-prev));
    else
    u3 +=(0*(clock1-prev));

    switch (currentevent->type) {
    case 1:                                 
      e1();
      break;

    case 2:                                                 
      e2();
      break;

    case 3:                                                   
      e3();    
      break;

    case 4:                                                    
      d1();
      break;

     case 5:                                                    
      d2();
      break;

     case 6:                                                    
      d3();
      break;

     case 7:                                                      
      r1();
	  break;
     case 8:                                                   
      r2();
      break;

    }
    delete currentevent;
    if (Nsdep > 5000000) 
done=1;        
  }
through1= N1dep/clock1;
through2= N2dep/clock1;
through3= N3dep/clock1;

util1= u1/clock1;
util2= u2/clock1;
util3= u3/clock1;

ewaitin1= EN1/N1dep;
ewaitin2= EN2/N2dep;
ewaitin3= EN3/N3dep;

EN1= EN1/clock1;
EN2= EN2/clock1;
EN3= EN3/clock1;

cout<<endl<<" The expected number of customers in queue1 is :"<<EN1;
cout<<endl<<" The expected waiting time in queue1 is :"<<ewaitin1;
cout<<endl<<" The throughput of queue1 is "<<through1;
cout<<endl<<" The utilization of queue1 :"<<util1;

cout<<endl<<" The expected number of customers in queue2is :"<<EN2;
cout<<endl<<" The expected waiting time in queue2 is :"<<ewaitin2;
cout<<endl<<" The throughput of queue2 is "<<through2;
cout<<endl<<" The utilization of queue2 :"<<util2;

cout<<endl<<" The expected number of customers in queue3 is :"<<EN3;
cout<<endl<<" The expected waiting time in queue1 is :"<<ewaitin3;
cout<<endl<<" The throughput of queue2 is "<<through3;
cout<<endl<<" The utilization of queue2 :"<<util3;

}
void theortical()
{
  double theta1=(lamda*rs1)/(1-r11);
  double  theta3=((theta1*r13)+(lamda*rs2))/(1-r32);
  double theta2=(lamda*rs2)+(theta3*r32);
  double util1t=theta1/mu1; 
  double util2t=theta2/mu2;
  double util3t=theta3/mu3;
  double EN1t=util1t/(1-util1t);
  double EN2t=util2t/(1-util2t);
  double EN3t=util3t/(1-util3t);
  double ewaitin1t=EN1t/theta1;
  double ewaitin2t=EN2t/theta2;
  double ewaitin3t=EN3t/theta3;
  cout<<endl<<" Theoretical values:";
  cout<<endl<<" The expected number of customers in queue1 is :"<<EN1t;
cout<<endl<<" The expected waiting time in queue1 is :"<<ewaitin1t;
cout<<endl<<" The throughput of queue1 is "<<theta1;
cout<<endl<<" The utilization of queue1 :"<<util1t;

cout<<endl<<" The expected number of customers in queue2is :"<<EN2t;
cout<<endl<<" The expected waiting time in queue2 is :"<<ewaitin2t;
cout<<endl<<" The throughput of queue2 is "<<theta2;
cout<<endl<<" The utilization of queue2 :"<<util2;

cout<<endl<<" The expected number of customers in queue3 is :"<<EN3t;
cout<<endl<<" The expected waiting time in queue1 is :"<<ewaitin3t;
cout<<endl<<" The throughput of queue2 is "<<theta3;
cout<<endl<<" The utilization of queue2 :"<<util3t;
}

int main()
{
cout<<endl<<"Enter the value of lamda : ";
cin>>lamda;
cout<<endl<<"Enter the value of mu1:";
cin>>mu1;
cout<<endl<<"Enter the value of mu2:";
cin>>mu2;
cout<<endl<<"Enter the value of mu3:";
cin>>mu3;
cout<<endl<<"Enter the value of rs1:";
cin>>rs1;
cout<<endl<<"Enter the value of rs2:";
cin>>rs2;
cout<<endl<<"Enter the value of r11:";
cin>>r11;
cout<<endl<<"Enter the value of r3d:";
cin>>r3d;
cout<<endl<<"Enter the value of r32:";
cin>>r32;
cout<<endl<<"Enter the value of r13:";
cin>>r13;
practical();
theortical();
}
