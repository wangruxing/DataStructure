#include <stdio.h>
#include <math.h>
#include <string.h>
#define MAX_STACK_SIZE 100 /* maximum stack size */
#define MAX_EXPR_SIZE 100 /* max size of expression */

// infix --> postfix
// 2. 逐步輸出過程
typedef enum {lparen, rparen, plus, minus, times, divide, 
	mod, eos, operand, blank } precedence;

char expr[MAX_EXPR_SIZE]; /* input string */
char result[MAX_EXPR_SIZE];
char *str = result;
int top = -1;
char eexpr[MAX_EXPR_SIZE]; /* input string */
int etop = -1;
int value=0;
int estack[MAX_STACK_SIZE];
// ISP(堆疊內優先權):In Stack Priority
// ICP(輸入優先權):In Coming Priority
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
    if(top == -1){ 
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
    	case ' ': return blank; // 空白
    	case '\0': return eos; // 空字符
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
    // get_token(&symbol, &n): &symbol, &n取址(變數位置)
    // 運算子(operator): + - * / 
    // 運算元(operand) : 1 2 3 4
    for(token = get_token(&symbol, &n); token != eos;token = get_token(&symbol, &n)) {
        //printf("symbol=%c\t", symbol);
        if(token != blank) { // token不是空白
            if(token == operand) { // token是運算元
                *str++=symbol; 
            }
            else if(token == rparen) { // token是右括號
                *str++=' ';
                // 直到找到左括號
                while(stack[top] != lparen){ // 把stack輸出直到遇到左括號
                    print_token(pop());
                }     
                pop();
            }
            else {  // token是plus, minus, times, divide, mod
                *str++=' '; 
                while(isp[stack[top]] >= icp[token])
                    print_token(pop());
                push(token);
            }
        }
    }
    *str++=' '; 
    // 把stack清空
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
    char str[80];
    printf("%s", "Please input infix: ");
    scanf("%s", str);

    // 如果要進行字串複製，可以使用 strcpy() 函式
    // 第一個參數是目的字元陣列，第二個參數是來源字串
	strcpy(expr, str);
	printf("infix  : %s", expr);
	postfix();
	printf("postfix: %s\n", result);
	strcpy(eexpr, result);
	printf("result : %d\n", eval());
}