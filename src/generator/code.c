/*
 * @Author: yinn
 * @Date: 2022-12-07 13:45:12
 * @LastEditTime: 2022-12-07 16:51:50
 * @Description:
 */

#include"stdio.h"
#include"ast.h"

FILE* outfile;

int putln(char* str) {
    char* s = (char*)malloc(sizeof(str) + 2 * sizeof(char));
    sprintf(s, "%s\n", str);
    int res = fputs(s, outfile);
    free(s);
    return res;
}

void generator(ASTNode* ast, FILE* f) {
    outfile = f;

}

void gen(ASTNode* ast) {
    if (ast == NULL) return;
    
    gen(ast->left);
    gen(ast->right);

    
}



/*
.text
.globl doNone
doNone:
    pushq %rbp
    movq %rsp, %rbp
    leave
    ret
.type doNone, @function
.size doNone, .-doNone
 */

 /*
 .data
 .balign 4
 .globl yy
 yy:
     .int 0
  */

  // .section .note.GNU-stack,"",@progbits

// Print out the assembly preamble
void cgpreamble()
{
    // fputs(
    //     "\t.text\n"
    //     ".LC0:\n"
    //     "\t.string\t\"%d\\n\"\n"
    //     "printint:\n"
    //     "\tpushq\t%rbp\n"
    //     "\tmovq\t%rsp, %rbp\n"
    //     "\tsubq\t$16, %rsp\n"
    //     "\tmovl\t%edi, -4(%rbp)\n"
    //     "\tmovl\t-4(%rbp), %eax\n"
    //     "\tmovl\t%eax, %esi\n"
    //     "\tleaq	.LC0(%rip), %rdi\n"
    //     "\tmovl	$0, %eax\n"
    //     "\tcall	printf@PLT\n"
    //     "\tnop\n"
    //     "\tleave\n"
    //     "\tret\n"
    //     "\n"
    //     "\t.globl\tmain\n"
    //     "\t.type\tmain, @function\n"
    //     "main:\n"
    //     "\tpushq\t%rbp\n"
    //     "\tmovq	%rsp, %rbp\n",
    //     Outfile);
}