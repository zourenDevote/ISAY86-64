//
// Created by 20580 on 2023/1/10.
//

#ifndef Y8664_ASSEMBER_CHECKER_H
#define Y8664_ASSEMBER_CHECKER_H

#include "assember_ast.h"
#include <set>

class AstBaseVisitor{
public:
    AstBaseVisitor() = default;

    virtual void visit(AssemblyCode* v) = 0;
    virtual void visit(AssemblyInstNode* v) = 0;
    virtual void visit(LabelDeclNode* v) = 0;
    virtual void visit(MainDeclNode* v) = 0;
    virtual void visit(PosDeclNode* v) = 0;
    virtual void visit(FillDeclNode* v) = 0;
    virtual void visit(QuadDeclNode* v) = 0;
    virtual void visit(InstNode* v) = 0;
    virtual void visit(OperandNode* v) = 0;
};

/// 0 -- INFO
/// 1 -- WARNING
/// 2 -- ERROR
/// 3 -- FETAL
struct check_result{
    LineNo line_no;
    int statue;
    std::string reason;
};

// 从汇编器的ast构建语法树
class AssemblyVisitor : public AstBaseVisitor{
public:
    AssemblyVisitor() = default;

    void visit(AssemblyCode *v) override;
    void visit(AssemblyInstNode *v) override;
    void visit(FillDeclNode *v) override;
    void visit(InstNode *v) override;
    void visit(LabelDeclNode *v) override;
    void visit(MainDeclNode *v) override;
    void visit(OperandNode *v) override;
    void visit(PosDeclNode *v) override;
    void visit(QuadDeclNode *v) override;

public:
    // 重置Checker的标志和检查结果
    void reset();
    [[nodiscard]] const std::vector<check_result>& getCheckResult() const { return chk_results; }
    [[nodiscard]] bool hasStartMainEntry() const { return haveMain; }
private:
    std::vector<check_result> chk_results;
    bool haveMain;                          // 是否存在主函数入口
    bool haveError;                         // 是否检测出错误
    Quad currentAddress;                    // 当前的地址
    std::set<std::string> label_set;        // 记录声明的标号

};

#endif //Y8664_ASSEMBER_CHECKER_H
