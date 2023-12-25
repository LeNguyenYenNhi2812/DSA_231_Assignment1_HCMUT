#include "main.h"
//extern int MAXSIZE;
class imp_res : public Restaurant
{
	
	public:	
	customer* inRescur=nullptr;
	int inResSize=0;

	customer* inQueuecur=nullptr;
	int inQueueSize=0;
	customer* inQueueHead=nullptr;

	customer* orderInResHead=nullptr;
	customer* orderInRescur=nullptr;
	int orderInResSize=0;
		imp_res() {};
bool duyngadocton(string name) // FUNCTION RED
{
	if(inResSize<=0) return false;
	if(inResSize==1) 
	{
		if(inRescur->name==name) return true;
	}
	else
	{
	customer* temp = inRescur->next;
	while(temp!= inRescur)
	{
		if(temp->name == name) return true;
		temp=temp->next;
	}
	}
	if(inQueueSize>0)
	{
	customer* temp =inQueuecur->next;
	while(temp!= inQueuecur)
	{
		if(temp->name == name) return true;
		temp=temp->next;
	}
	}
	
	return false;
}
		void RED(string name, int energy)
		{
			
			 if(energy==0) return;
			 if(inResSize==  MAXSIZE  && inQueueSize == MAXSIZE) return;
			 if(inRescur!=nullptr) 
			 {
			if(duyngadocton(name)==true) return;
			 }
			 customer *cus = new customer (name, energy, nullptr, nullptr);
			 
			if(inResSize==0)
			{
				inRescur=cus; 
				inRescur->next=inRescur;
				inRescur->prev=inRescur;
				inResSize++;
			}
			else if(inResSize < MAXSIZE/2  )
			{
				if(energy >= inRescur->energy)
				{
					cus->next=inRescur->next;
					inRescur->next->prev=cus;
					inRescur->next=cus;
					cus->prev=inRescur;
					inRescur=cus;
					inResSize++; 
				}
				else if(energy<inRescur->energy)
				{
					
					cus->next=inRescur;
					cus->prev=inRescur->prev;
					inRescur->prev->next=cus;
					inRescur->prev=cus;
					inRescur=cus;
					inResSize++;
				}
			}
			else if(inResSize< MAXSIZE  )
			{ 
				int max=INT16_MIN;
				customer* temp= inRescur;
				customer* newcur = nullptr;
				while(temp!=nullptr)
				{
					if(abs( temp->energy - energy) > max)
					{
						max = abs(temp->energy - energy);
						newcur=temp;
					}
					temp=temp->next;
					if(temp==inRescur) break;
				} 
				if(energy-newcur->energy >=0)
				{
					cus->next=newcur->next;
					newcur->next->prev=cus;
					newcur->next=cus;
					cus->prev=newcur;
					inRescur=cus; 
					inResSize++;
				}
				else 
				{
					cus->prev=newcur->prev;
					newcur->prev->next=cus;
					newcur->prev=cus;
					cus->next=newcur;
					inRescur=cus;
					inResSize++;
				}
				

			}
			else if(inQueueSize==0)
			{
				inQueuecur=cus;
				inQueueHead=cus;
				inQueuecur->next=inQueuecur;
				inQueuecur->prev=inQueuecur;
				inQueueSize++;
			}
			else if(inQueueSize<  MAXSIZE  )
			{
				inQueuecur->next=cus;
				cus->prev=inQueuecur;
				cus->next=inQueueHead;
				inQueueHead->prev=cus;
				inQueuecur=cus;
				inQueueSize++;
			}
		
			customer* c = new customer (name, energy, nullptr, nullptr);
			if(orderInResHead==nullptr)
			{
				orderInResHead=c;
				orderInRescur=c;
				orderInRescur->next=c;
				orderInRescur->prev=c;
				orderInResSize=1;
			}
			else
			{
				orderInRescur->next=c;
				c->prev=orderInRescur;
				c->next=orderInResHead;
				orderInResHead->prev=c;
				orderInRescur=c;
				orderInResSize++;
			}
			
		}
 void deleteInRes(string namecus) // FUNCTION BLUE
 {
	if(inResSize<=0) return;
	if(inResSize==1)
	{
		customer* temp1=inRescur;
		inRescur->prev=nullptr;
		inRescur->next=nullptr;
		inResSize=0;
		temp1->next=nullptr;
		temp1->prev=nullptr;
		delete temp1;
		return;
	}
	customer* temp2=inRescur;
	
	for(int i=0;i<inResSize;++i)
	{
		if(temp2->name==namecus) break; 
		temp2=temp2->next;
	}
	if(temp2->energy >0) 
	{
		inRescur=temp2->next;
	}
	else
	{
		inRescur=temp2->prev;
	}
	if(inResSize>1)
	{
		
		customer* prevcus=temp2->prev;
		temp2->next->prev=prevcus;
		prevcus->next=temp2->next;
		temp2->next=nullptr;
		temp2->prev=nullptr;
		delete temp2;
		inResSize--;	
	}

}

		void BLUE(int num)
		{
			
			if(num<=0) return; 
			if(num > MAXSIZE || num>inResSize)
			{
			while ( inResSize!=0 && orderInResSize!=0)
			{
				string namecus=orderInResHead->name; 
				if(orderInResSize==1)
				{
					customer* temp=orderInResHead;
					orderInRescur=nullptr;
					orderInResHead=nullptr;
					orderInResSize=0;
					temp->next=nullptr;
					temp->prev=nullptr;
					delete temp;
				}
				else{
				orderInRescur->next=orderInResHead->next;
				orderInResHead->next->prev=orderInRescur;
				customer* temp=orderInResHead;
				orderInResHead=orderInResHead->next;
				temp->prev=nullptr;
				temp->next=nullptr;
				delete temp;
				orderInResSize-=1;
				}
				
				deleteInRes(namecus);
				
				}
			}
			else 
			{
			while (num !=0 && orderInResSize!=0)
			{
				string namecus=orderInResHead->name;
				orderInRescur->next=orderInResHead->next;
				orderInResHead->next->prev=orderInRescur;
				customer* temp=orderInResHead;
				orderInResHead=orderInResHead->next;
				temp->prev=nullptr;
				temp->next=nullptr;
				delete temp;
				
				deleteInRes(namecus);
				num-=1;
				orderInResSize-=1;
				}
			}
		
			if(inResSize < MAXSIZE)
			{
				while (inResSize!=MAXSIZE && inQueueSize!=0)
				{
					string name=inQueueHead->name;
					int energy=inQueueHead->energy;
					inQueuecur->next=inQueueHead->next;
					inQueueHead->next->prev=inQueuecur;
					customer* temp=inQueueHead;
					inQueueHead=inQueueHead->next;
					temp->next=nullptr;
					temp->prev=nullptr;
					delete temp;
					inQueueSize-=1;
					RED(name,energy);

				}
				
			}
			
		}

void swapnode1(customer* head, customer* tail) // swap cho queue
{
			if(head==nullptr || tail==nullptr) return;
			if(head==tail) return;
			if(head==inQueueHead) inQueueHead=tail;
			if(head->next==tail)
			{
				customer* t1=head->prev;
				customer* t2=tail->next;
				head->next=t2;
				head->prev=tail;
				tail->next=head;
				tail->prev=t1;
				t1->next=tail;
				t2->prev=head;
			}
			else{
			customer* temp= new customer(head->name,head->energy,nullptr,nullptr);
			temp->next=head->next;
			temp->prev=head->prev;
			head->next->prev=temp;
			head->prev->next=temp;

			head->next=tail->next;
			head->prev=tail->prev;
			tail->next->prev=head;
			tail->prev->next=head;

			tail->next=temp->next;
			tail->prev=temp->prev;
			temp->next->prev=tail;
			temp->prev->next=tail;

			temp->next=nullptr;
			temp->prev=nullptr;
			delete temp;
			}

}
		
		int inssort2( int A ,int n, int incr)
		{
			int res=0; // số lần swap 
			for(int i=incr ; i< n ; i+=incr)
			{
				int j=i;
				while(j>=incr)
				{
					customer* cus1=inQueueHead;
					customer* cus2=inQueueHead;
					for(int x=0; x< j+A ;x++)
					{
						cus2=cus2->next;
					}
					for(int y=0; y< j-incr+A;y++)
					{
						cus1=cus1->next;
					}
					if(abs(cus1->energy) < abs(cus2->energy))
					{
						swapnode1(cus1,cus2);
						res++;
					}
					j-=incr;
				}
				
			}
			return res;
		}
		void PURPLE()
		{
		
			 if(inQueueSize<=1) return;
			 customer* maxEnergycus=inQueueHead;
			 int n=0; // n là số lượng khách từ đầu hàng tới maxenergy
			 int sortCount=0;// đếm số lần sort
			 customer* temp=inQueueHead;
			 for(int i=1;i<inQueueSize;++i)
			 {
				if(abs(temp->energy) >= abs(maxEnergycus->energy))
				{
					maxEnergycus=temp;
					n=i;
				}
				temp=temp->next; 
			 }
			
			for(int i=n/2 ; i>2 ; i/=2)
			{
				for(int j=0 ; j < i; j++ )
				{
					sortCount+=inssort2(j,n-j,i);
				}
			}
			sortCount+=inssort2(0,n,1);
			
			BLUE(sortCount%MAXSIZE);

		}

void swapnode(customer* head, customer* tail) // swap cho inres của reversal
{
			if(head==nullptr || tail==nullptr) return;
			if(head->next==tail)
			{
				if(tail->next==head)
				{
					customer* temp=head;
					head=tail;
					tail=temp;
				}
				else
				{
				customer* t1=head->prev;
				customer* t2=tail->next;
				head->next=t2;
				head->prev=tail;
				tail->next=head;
				tail->prev=t1;
				t1->next=tail;
				t2->prev=head;
				}
			}
			else{
			customer* temp= new customer(head->name,head->energy,nullptr,nullptr);
			temp->next=head->next;
			temp->prev=head->prev;
			head->next->prev=temp;
			head->prev->next=temp;

			head->next=tail->next;
			head->prev=tail->prev;
			tail->next->prev=head;
			tail->prev->next=head;

			tail->next=temp->next;
			tail->prev=temp->prev;
			temp->next->prev=tail;
			temp->prev->next=tail;

			temp->next=nullptr;
			temp->prev=nullptr;
			delete temp;
			}
}
		void REVERSAL()
		{
			
	
	if(inResSize <= 1) return;			
	customer* head = nullptr; 
	customer* tail = nullptr;

	head = inRescur;
	for(int i = 0; i < inResSize; i++)
	{
		if(head->energy > 0) head = head->prev;
	}

	tail = inRescur->next;
	for(int i = 0; i < inResSize; i++)
	{
		if(tail->energy > 0) tail = tail->next;

	}
	if(head->energy < 0 && head != tail)
	{

		for(int i = 0; i < inResSize / 2; i++) // hàm dò trong inres
		{
			this->swapnode(head, tail); 
			customer* temp = head;
			head = tail;
			tail = temp;
			temp = nullptr;

			head = head->prev;
			for(int i = 0; i < inResSize; i++)
			{
				if(head->energy > 0) head = head->prev;

			}

			if(head == tail) break;		
			tail = tail->next;
			for(int i = 0; i < inResSize ; i++)
			{
				if(tail->energy > 0) tail = tail->next;

			}	
			if(head == tail) break;	
		}
	}
//! đảo chú thuật sư
head = inRescur;
	for(int i = 0; i < inResSize; i++)
	{
		if(head->energy < 0) head = head->prev;
	}

	tail = inRescur->next;
	for(int i = 0; i < inResSize; i++)
	{
		if(tail->energy < 0) tail = tail->next;

	}

	if(head->energy > 0 && head != tail)
	{
		for(int i = 0; i < inResSize / 2; i++)
		{
			this->swapnode(head, tail); //! đổi giá trị bên trong con trỏ

			customer* temp = head;
			head = tail;
			tail = temp;
			temp = nullptr;

			head = head->prev;
			for(int i = 0; i < inResSize; i++)
			{
				if(head->energy < 0) head = head->prev;

			}

			if(head == tail) break;		

			tail = tail->next;
			for(int i = 0; i < inResSize ; i++)
			{
				if(tail->energy < 0) tail = tail->next;

			}	
			if(head == tail) break;	
		}
	}
		
    
			
		}
		void deleteInRes1(string namecus) // FUNCTION DOMAIN
 {
	if(inResSize<=0) return;
	customer* temp1=inRescur;
	
	
	for(int i=0;i<inResSize;++i)
	{
		if(temp1->name==namecus) break; 
		temp1=temp1->next;
	}
	if(temp1->name != namecus) return;
	
	if(temp1->energy > 0) inRescur=temp1->next;
		else inRescur=temp1->prev;
	
	if(inResSize==1)
	{
		inRescur->prev=nullptr;
		inRescur->next=nullptr;
		inResSize=0;
		temp1->next=nullptr;
		temp1->prev=nullptr;
		delete temp1;
	}
	else
	{
		customer* prevcus=temp1->prev;
		temp1->next->prev=prevcus;
		prevcus->next=temp1->next;
		temp1->next=nullptr;
		temp1->prev=nullptr;
		delete temp1;
		inResSize--;
	}
	
}
		void deleteInQueue(string namecus) //! HAM DOMAIN
{
	customer* temp1=inQueueHead;
	for(int i=0;i<inQueueSize;++i)
	{
		if(temp1->name==namecus) break; 
		temp1=temp1->next;
	}
	if(temp1==inQueueHead)
	inQueueHead=inQueueHead->next;
	if(inQueueSize==1)
	{
		inQueueHead->prev=nullptr;
		inQueueHead->next=nullptr;
		inQueueSize=0;
		delete temp1;
	}
	else
	{
		customer* prevcus=temp1->prev;
		temp1->next->prev=prevcus;
		prevcus->next=temp1->next;
		temp1->next=nullptr;
		temp1->prev=nullptr;
		delete temp1;
		inQueueSize--;
	}
	
}
		void deleteInOrder(string namecus)
		{
	customer* temp1=orderInResHead;
	for(int i=0;i<orderInResSize;++i)
	{
		if(temp1->name==namecus) break; 
		temp1=temp1->next;
	}
	if(temp1==orderInResHead)
	orderInResHead=orderInResHead->next;
	if(orderInResSize==1)
	{
		orderInResHead->prev=nullptr;
		orderInResHead->next=nullptr;
		orderInResSize=0;
		delete temp1;
	}
	else
	{
		customer* prevcus=temp1->prev;
		temp1->next->prev=prevcus;
		prevcus->next=temp1->next;
		temp1->next=nullptr;
		temp1->prev=nullptr;
		delete temp1;
		orderInResSize--;
	}
	
		}	
		void UNLIMITED_VOID()
		{
		
	if(inResSize<4) return;
			
	int MIN_TOTAL = INT16_MAX; //! đáp án cuối cùng
	customer* head = nullptr;
	customer* tail = nullptr; 
	int sizeMAX = 0; // độ dài lớn nhất của chuỗi
	customer* tempi = inRescur; 
	for(int i = 0; i < inResSize; i++)
	{
		int TOTAL = 0;  //! tổng từ chạy i -> i + inressize
		customer* tempj = tempi; //! khách hàng j
		for(int j = 0; j < inResSize; j++)
		{
		// tính tổng TOTAL, cập nhật head và tail khi số khách > 4 và TOTAL nhỏ bằng
			TOTAL +=  tempj->energy;
			if(j >= 3 && (MIN_TOTAL > TOTAL || MIN_TOTAL == TOTAL  && j + 1 >= sizeMAX))
			{
				head = tempi;
				tail = tempj;
				sizeMAX = j + 1;
				MIN_TOTAL = TOTAL;
			}

			tempj = tempj->next;
		}
		tempi = tempi->next;
	}			
	
	//^ chú ý nếu khách hàng đều là oán linh tail->Next = head

	customer* min = head;
	customer* temp = head->next; 
	int sizeHeadToMin = 1, sizeHeadToTail = 1;
	//TODO: tìm min energy đầu tiên, tính sizeHeadToMin và sizeHeadToTail
	while(temp != tail->next)
	{
		sizeHeadToTail ++;
		if(min->energy > temp->energy)
		{
			min = temp;
			sizeHeadToMin = sizeHeadToTail;
		}
		temp = temp->next;
	}
	for(int i = 0; i <= sizeHeadToTail - sizeHeadToMin; i++)
	{
		min->print();
		min = min->next;
	}
	
	for(int i = 0; i < sizeHeadToMin - 1; i++)
	{
		head->print();
		head = head->next;
	}

		}
		void DOMAIN_EXPANSION()
		{
			
			if(inResSize==0) return;
			int sumEnergyCTS=0;
			int sumEnergyOL=0;
			int numCTSres=0, numCTSqueue=0;
			int numOLres=0,numOLqueue=0;
			customer* temp=inRescur;
			int numInRes=inResSize;
			while(numInRes!=0)
			{
				if(temp->energy>0) 
				{
					sumEnergyCTS+=temp->energy;
					numCTSres++;
				}
				else 
				{
					sumEnergyOL+=temp->energy;
					numOLres++;
				}
				temp=temp->next;
				numInRes--;
			}
			 temp=inQueueHead;
			int numInQueue=inQueueSize;
			while(numInQueue!=0)
			{
				if(temp->energy>0) 
				{
					sumEnergyCTS+=temp->energy;
					numCTSqueue++;
				}
				else 
				{
					sumEnergyOL+=temp->energy;
					numOLqueue++;
				}
				temp=temp->next;
				numInQueue--;
			}
			if(sumEnergyCTS>=abs(sumEnergyOL))
			{
			customer* tempfind=orderInResHead;
			int numorderfind=orderInResSize;
			while(numorderfind!=0)
			{
				customer* n = tempfind->next;
				if(tempfind->energy<0) 
				{
				
				 if(inResSize>0 ) deleteInRes1(tempfind->name);
				else break;
				}
				tempfind=n;
				numorderfind--;
				
			}
				
			temp=inQueueHead;
			while(numOLqueue!=0)
			{
				customer* next=temp->next;
				if(temp->energy<0) 
				{
				deleteInQueue(temp->name);
				numOLqueue--;
				}
				temp=next;
			}
			customer* temporder=orderInResHead->prev;
			int numorder=orderInResSize;
			while(numorder!=0)
			{
				customer* p = temporder->prev;
				if(temporder->energy<0) 
				{
				
				temporder->print();
				deleteInOrder(temporder->name);
				}
				temporder = p;
				numorder--;
				
			}
			}
			else
			{
			customer* tempfind=orderInResHead;
			int numorderfind=orderInResSize;
			while(numorderfind!=0)
			{
				customer* n = tempfind->next;
				if(tempfind->energy>0) 
				{
				
				if(inResSize>0) deleteInRes1(tempfind->name);
				else break;
				}
				tempfind=n;
				numorderfind--;
				
			}
			temp=inQueueHead;
			while(numCTSqueue!=0)
			{
				customer* next=temp->next;
				if(temp->energy>0) 
				{
				deleteInQueue(temp->name);
				numCTSqueue--;
				}
				temp=next;
			}
			customer* temporder=orderInResHead->prev;
			int numorder=orderInResSize;
			while(numorder!=0)
			{
				customer* p=temporder->prev;
				if(temporder->energy>0) 
				{
				
				temporder->print();
				deleteInOrder(temporder->name);
				
				}
				temporder=p;
				numorder--;
			}
			}
			if(inResSize < MAXSIZE) 
			{
				while (inResSize!=MAXSIZE && inQueueSize!=0)
				{
					string name=inQueueHead->name;
					int energy=inQueueHead->energy;
					inQueuecur->next=inQueueHead->next;
					inQueueHead->next->prev=inQueuecur;
					customer* temp=inQueueHead;
					inQueueHead=inQueueHead->next;
					temp->next=nullptr;
					temp->prev=nullptr;
					delete temp;
					inQueueSize-=1;
					RED(name,energy);

				}
			}

			
		}
		void LIGHT(int num)
		{
			
			if(num==0)
			{
				customer* temp=inQueueHead;
				if(inQueueSize==0) return;
				else
				{
					int numQueue=inQueueSize;
					while(numQueue!=0)
					{
						
						temp->print();
						temp=temp->next;
						numQueue-=1;
					}
				}
			}
			else if (num>0)
			{
				if(inResSize==0) return;
				else
				{
					customer* temp=inRescur;
					int numInRes=inResSize;
					while(numInRes!=0)
					{
						
						temp->print();
						temp=temp->next;
						numInRes-=1;
					}
				}
			}
			else if(num<0)
			{
				customer* temp=inRescur;
					int numInRes=inResSize;
					while(numInRes!=0)
					{
						
						temp->print();
						temp=temp->prev;
						numInRes-=1;
					}
			}
		}
};