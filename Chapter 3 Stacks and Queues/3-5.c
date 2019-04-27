#include <stdio.h>
#include <math.h>
#include <string.h>
#define MAX_STACK_SIZE 100 /* maximum stack size */
#define MAX_EXPR_SIZE 100 /* max size of expression */

// infix --> postfix
// 1. 須寫上註解
// 2. 做成使用者輸入中置式
// 3. 最好將變數統一跟課本相近
typedef enum {lparen, rparen, plus, minus, times, divide, 
	mod, eos, operand, blank } precedence;

char expr[MAX_EXPR_SIZE]; /* input string */
char result[MAX_EXPR_SIZE];
char *str=result;
int top = -1;
char eexpr[MAX_EXPR_SIZE]; /* input string */
int etop = -1;
int value=0;
int estack[MAX_STACK_SIZE];
static int isp[] = {0,19,12,12,13,13,13,0};
static int icp[] = {20,19,12,12,13,13,13,0};
precedence stack[MAX_STACK_SIZE];
/* isp and icp arrays ? index is value of precedence lparen, rparen, 
	plus, minus, times, divide, mode, eos */

void push(precedence item){
    if(top >= MAX_STACK_SIZE - 1) {
        printf("stack_full()\n");
        return;
    }
    stack[++top] = item;
}                    

precedence pop() {
    if(top == -1)
	{ 
        printf("stack_empty()\n");
	}
	return stack[(top)--];
}

int isempty(){ 
    if(top == -1) 
        return(1); 
    else 
        return(0); 
}

int isfull(){ 
    if(top >= MAX_STACK_SIZE -1) 
        return(1); 
    else 
        return(0); 
}


precedence get_token(char *symbol, int *n) {
    *symbol = expr[(*n)++];
    switch(*symbol) {
	    case '(': return lparen;
	    case ')': return rparen;
	    case '+': return plus;
    	case '-': return minus;
    	case '/': return divide;
    	case '*': return times;
	    case '%': return mod;
    	case ' ': return blank;
    	case '\0': return eos;
    	default: return operand;
    }
}

precedence print_token(precedence t) {
    switch(t) {
    	case lparen : *str++='(';*str++=' ';break;
    	case rparen : *str++=')';*str++=' '; break;
	    case plus : *str++='+'; break;
    	case minus : *str++='-';*str++=' '; break;
    	case divide : *str++='/';*str++=' '; break;
    	case times : *str++='*';*str++=' '; break;
	    case mod : *str++='%';*str++=' '; break;
    	case eos : printf("eos"); break;
    	default: printf("\n");
    }
    return 0;
}

void postfix(void) {
    char symbol;
    precedence token;
    int n = 0;
    top = 0;
    stack[0] = eos;
    for(token = get_token(&symbol, &n); token != eos;token = get_token(&symbol, &n)) {
        if(token != blank) {
            if(token == operand) { 
                *str++=symbol; 
            }
            else if(token == rparen) { 
                *str++=' ';
                while(stack[top] != lparen)
	                print_token(pop());
                pop();
            }
            else { 
                *str++=' '; 
                while(isp[stack[top]] >= icp[token])
                    print_token(pop());
                push(token);
            }
        }
    }
    *str++=' '; 
    while((token = pop()) != eos)
        print_token(token);
    *str++='\0';
    printf("\n");
}

void epush(int item){
    if(etop >= MAX_STACK_SIZE - 1) {
        printf("stack_full()\n");
        return;
    }
    estack[++etop] = item;
}                    

int epop() {
	if(etop == -1){ 
		printf("stack_empty()\n"); 
	}
	return estack[(etop)--];
}

int eisempty(){ 
    if(etop == -1) 
        return(1); 
    else 
        return(0);
}

int eisfull(){ 
    if(etop >= MAX_STACK_SIZE -1) 
        return(1); 
    else 
        return(0);
}

precedence eget_token(char *esymbol, int *n) {
    *esymbol = eexpr[(*n)++];
    switch(*esymbol) {
        case '(': return lparen;
        case ')': return rparen;
        case '+': return plus;
        case '-': return minus;
        case '/': return divide;
        case '*': return times;
        case '%': return mod;
        case ' ': return blank;
        case '\0': return eos;
        default: {
            value=(*esymbol-'0');
            while(eexpr[(*n)] >= '0' && eexpr[(*n)] <='9'){
                *esymbol=eexpr[(*n)++];
                value=value*10+(*esymbol-'0');
            }; 	
            return operand;
        }
    }
}

precedence eprint_token(precedence  t) {
    switch(t) {
        case lparen : printf("(" ); break;
        case rparen : printf(")" ); break;
        case plus : printf("+" ); break;
        case minus : printf("-" ); break;
        case divide : printf("/" ); break;
        case times : printf("*" ); break;
        case mod : printf("%" ); break;
        case eos : printf("eos" ); break;
        default: printf("\n");
    } 
    return 0;
}

int eval(void){
    precedence token;
    char esymbol;
    int op1, op2;
    int n = 0;
    etop = -1;
    token = eget_token(&esymbol, &n);
    while (token != eos) {
        if(token == operand)
            epush(value);
        else if (token != blank) {
            op2 = epop();
            op1 = epop();
            switch(token) {
                case blank: break;
                case plus: epush(op1 + op2);break;
                case minus: epush(op1 - op2);break;
                case times: epush(op1 * op2);break;
                case divide: epush(op1 / op2);break;
                case mod: epush(op1 % op2);
            }
        }
        token = eget_token(&esymbol, &n);
    }
    return epop();
}

int main(){
	strcpy(expr, "36+72*435/(2+3)");
	printf("%s", expr);
	postfix();
	printf("%s\n", result);
	strcpy(eexpr, result);
	printf("%d\n", eval());
}