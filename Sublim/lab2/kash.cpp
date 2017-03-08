/*
	const char *p=strpbrk(str,operations);
	int l=0;
	while(p!=NULL){
			//cout << p[0] << endl;
			strcpy(&numb[l],p);
			l++;
			p=strpbrk(p+1,operations);
	}

	for(int i=0; i<l;i++)
	cout<<numb[i];

	const char *q=strpbrk(str,number);
	int k=0;
	while(q!=NULL){
			//cout <<endl;
			opera[k]=atoi(q);	
			k++;
			for(int i=0;;i++){
				if(q[i] >= '0' && q[i] <='9'){
					//cout << q[i];
				} else {q+=i; break;}
			}
			q=strpbrk(q+1,number);
			if(q==NULL) break;
	}
	cout << endl << endl;
	for(int i=0; i<k;i++)
	cout<<opera[i]<<",";
	return result;

	/*Приоритет
	int a_priority(char more,char less){
       	if (more == '(') return 0;
       	if (more == '+' || less == '-') return 1;
       	if (more) == '^' ) return 1;
       	if ((less == '*' || less == '/')&&(more == '*' || more == '/')) return 1;
       return 0;
}*/