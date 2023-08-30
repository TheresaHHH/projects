ListNode* middleNode(ListNode* head) {
      if(head==nullptr)      {return head;}
      stack<ListNode*>stack;
	  //will return this newhead
      ListNode* newhead=head;
	  //add all nodes to the stack
      while(head!=nullptr)
      {
          stack.push(head);
          head=head->next;
      }
	  //re-set head to the orginal node
      head= newhead;
      while(!stack.empty())
      {
          if(stack.top()==head  ) //one middle node case
          {
              newhead=head;
              return newhead;
          }else if(head->next == stack.top())  //two middle nodes case
          {
              newhead=head->next;
              return newhead;
          }
		  //advance to the next nodes
		  stack.pop();
          head=head->next;;
      }
    return head; //other cases, ex: only one node in the list
	}