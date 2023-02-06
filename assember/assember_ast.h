/**
 * Author: Devote
 * Date: 20230110
 * Overview: This file is the ast define
 * of the assembly code.
 */

#ifndef Y8664_ASSEMBER_AST_H
#define Y8664_ASSEMBER_AST_H

#include "../base.h"

struct LineNo{
    int row;
    int column;
    int file_index;
};

enum class AstType {
    operand,
    inst,
    quad,
    fill,
    pos,
    main,
    stack,
    label,
    assembly_stmt,
    assembly_code
};

class BaseAst{
public:
    BaseAst() : line_no() {}
    virtual AstType astType() = 0;
    [[nodiscard]] LineNo getLineNo() const { return line_no; }
    void setLineNo(const LineNo& line) { this->line_no = line; }
private:
    LineNo line_no;
};

class OperandNode : public BaseAst{
public:
    OperandNode(const std::string&, bool);
    explicit OperandNode(Quad number);
    [[nodiscard]] bool isLabel() const { return is_label; }
    [[nodiscard]] bool isReg() const { return is_reg; }
    [[nodiscard]] bool isQuad() const { return is_quad; }

    [[nodiscard]] std::string getRegName() const { return reg_or_label; }
    [[nodiscard]] std::string getLabelName() const { return reg_or_label; }
    [[nodiscard]] Quad getNumber() const { return number; }

    AstType astType() override { return AstType::operand; }
private:
    std::string reg_or_label;
    Quad number;
    const bool is_label;
    const bool is_quad;
    const bool is_reg;
};

class InstNode : public BaseAst{
public:
    InstNode(const std::string& inst, Byte op);
    [[nodiscard]] std::string getInst() const { return inst; }
    [[nodiscard]] Byte getInstOp() const { return inst_op; }

    AstType astType() override { return AstType::inst; }
private:
    std::string inst;   // 汇编指令字符串
    Byte inst_op;       // 汇编指令机器码标号
};

class QuadDeclNode : public BaseAst {
public:
    explicit QuadDeclNode(const std::vector<Quad>& data);

    AstType astType() override { return AstType::quad; }
    [[nodiscard]] const std::vector<Quad>& getDataDecl() const { return numbers; }
public:

private:
    std::vector<Quad> numbers;

public:
    [[nodiscard]] Quad getInstStartAddress() const { return address; }
    void setInstStartAddress(Quad addr) { address = addr; }
private:
    Quad address;
};

class FillDeclNode : public BaseAst {
public:
    FillDeclNode(Quad number, Byte value);

    [[nodiscard]] Quad getFillSize() const { return fill_size; }
    [[nodiscard]] Byte getFillValue() const { return fill_value; }

    AstType astType() override { return AstType::fill; }
private:
    Quad fill_size;     // 填充大小
    Byte fill_value;    // 填充值
public:
    [[nodiscard]] Quad getInstStartAddress() const { return address; }
    void setInstStartAddress(Quad addr) { address = addr; }
private:
    Quad address;
};

class PosDeclNode : public BaseAst {
public:
    explicit PosDeclNode(Quad addr);
    [[nodiscard]] Quad getAddress() const { return address; }

    AstType astType() override { return AstType::pos; }
private:
    Quad address;
};

class MainDeclNode : public BaseAst {
public:
    MainDeclNode() : address() {}
    AstType astType() override { return AstType::main; }

public:
    [[nodiscard]] Quad getInstStartAddress() const { return address; }
    void setInstStartAddress(Quad addr) { address = addr; }

private:
    Quad address;       // 堆栈初始指针
};

class StackDeclNode : public BaseAst {
public:
    StackDeclNode(Quad size, Quad addr);

    [[nodiscard]] Quad getStackSize() const { return stack_size; };
    [[nodiscard]] Quad getAddress() const { return address; }

    AstType astType() override { return AstType::stack; }
private:
    Quad stack_size;    // 栈的大小
    Quad address;       // 堆栈初始指针
};

class LabelDeclNode : public BaseAst {
public:
    explicit LabelDeclNode(const std::string& label_name);

    [[nodiscard]] std::string getLabelName() const { return label_name; }
    AstType astType() override { return AstType::label; }
private:
    std::string label_name;

public:
    [[nodiscard]] Quad getInstStartAddress() const { return address; }
    void setInstStartAddress(Quad addr) { address = addr; }
private:
    Quad address;
};

class AssemblyInstNode : public BaseAst {
public:
    AssemblyInstNode(InstNode*, OperandNode* = nullptr, OperandNode* = nullptr);

    AstType astType() override { return AstType::assembly_stmt; }

    [[nodiscard]] InstNode* getInst() const { return inst; }
    [[nodiscard]] OperandNode* getFirstOperand() const { return op1; }
    [[nodiscard]] OperandNode* getSecondOperand() const { return op2; }
    [[nodiscard]] int getOperatorCount();

public:
    [[nodiscard]] Quad getInstStartAddress() const { return address; }
    void setInstStartAddress(Quad addr) { address = addr; }

private:
    InstNode* inst;
    OperandNode* op1;
    OperandNode* op2;

private:
    Quad address;
};

class AssemblyCode : public BaseAst {
public:
    AssemblyCode() = default;

    void addStmt(BaseAst* node) { stmts.push_back(node); }
    [[nodiscard]] const std::vector<BaseAst*>& getStmts() const { return stmts; }

    AstType astType() override { return AstType::assembly_code; }
private:
    std::vector<BaseAst*> stmts;
};



#endif //Y8664_ASSEMBER_AST_H
