#include <iostream>
#include <memory>
#include <fstream>

extern std::ofstream koopafile;  // 引用主文件中定义的全局文件对象

// 所有 AST 的基类
class BaseAST {
public:
    virtual ~BaseAST() = default;

    virtual void Dump() const = 0;
};


class CompUnitAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> func_def;

//    void Dump() const override {
//        std::cout << "CompUnitAST { ";
//        func_def->Dump();
//        std::cout << " }";
//    }
    void Dump() const override {
        func_def->Dump();
    }
};

class FuncDefAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> func_type;
    std::string ident;
    std::unique_ptr<BaseAST> block;

//    void Dump() const override {
//        std::cout << "FuncDefAST { ";
//        func_type->Dump();
//        std::cout << ", " << ident << ", ";
//        block->Dump();
//        std::cout << " }";
//    }
    void Dump() const override {
        koopafile << "fun ";
        koopafile << "@" << ident << "(): ";
        func_type->Dump();
        koopafile << "{\n";
        block->Dump();
        koopafile << " }";
    }
};

class FuncTypeAST : public BaseAST {
public:
    std::string func_type;

//    void Dump() const override {
//        std::cout << "FuncTypeAST { ";
//        std::cout << func_type ;
//        std::cout << " }";
//    }
    void Dump() const override {
        koopafile << "i32 ";
    }
};

class BlockAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> stmt;

//    void Dump() const override {
//        std::cout << "BlockAST { ";
//        stmt->Dump();
//        std::cout << " }";
//    }
    void Dump() const override {
        koopafile << "%entry:\n  ";
        stmt->Dump();
    }
};


class StmtAST : public BaseAST {
public:
    int num;

    void Dump() const override {
        koopafile << "ret " << num << std::endl;
    }
};