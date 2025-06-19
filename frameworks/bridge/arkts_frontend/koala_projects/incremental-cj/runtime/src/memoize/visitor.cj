macro package KoalaRuntime.memoize

import std.collection.*
import std.ast.*

class ReturnVisitor <: MemoVisitor {
    public override func visit(retExpr: ReturnExpr) {
        let hasReturnExpr = retExprIsEmpty(retExpr)
        if (hasReturnExpr) {
            retExpr.expr.traverse(MemoFuncVisitor(this.memoizedParamsNames))
            if(retExpr.expr.toTokens()[0].value != "__memo_scope") {
                retExpr.expr = parseExpr(quote(__memo_scope.recache( $(retExpr.expr.toTokens())) ))
            }
            breakTraverse()
        } else {
            retExpr.expr = parseExpr(quote(__memo_scope.recache(MEMO_UNIT)))
            breakTraverse()
        }
        return
    }
}

class RefExprVisitor <: Visitor {
    var memoizedParamsNames: ArrayList<String> = ArrayList()

    init(memoizedParamsNames: ArrayList<String>) {
        this.memoizedParamsNames = memoizedParamsNames
    }

    public override func visit(refExpr: RefExpr) {
        if (memoizedParamsNames.contains(refExpr.identifier.value)) {
            refExpr.identifier = Token(IDENTIFIER, "__memo_param_value_" + refExpr.identifier.value)
        }
    }
}

open class MemoVisitor <: Visitor {
    var memoizedParamsNames: ArrayList<String> = ArrayList()
    var memoizedParams: ArrayList<Node> = ArrayList()

    func memoizeParams(funcDecl: FuncDecl): ArrayList<Node> {
        var count = 0
        for (param in funcDecl.funcParams) {
            if(param.paramType is PrimitiveType || param.paramType is RefType) {
                let varName = Token(IDENTIFIER, "__memo_param_" + param.identifier.value)
                let varValue = Token(IDENTIFIER, param.identifier.value)
                let varDecl = VarDecl(quote(let $(varName) = getParameter(__memo_scope, $(count), $(varValue), $(param.identifier.value))))

                memoizedParamsNames.add(param.identifier.value)
                memoizedParams.add(varDecl)
                count++
            }
        }
        return memoizedParams
    }

    func memoizeParams(lambdaExpr: LambdaExpr): ArrayList<Node> {
        var count = 0
        for (param in lambdaExpr.funcParams) {
            let varName = Token(IDENTIFIER, "__memo_param_" + param.identifier.value)
            let varValue = Token(IDENTIFIER, param.identifier.value)
            let varDecl = VarDecl(quote(let $(varName) = getParameter(__memo_scope, $(count), $(varValue), $(param.identifier.value))))

            memoizedParamsNames.add(param.identifier.value)
            memoizedParams.add(varDecl)
            count++
        }
        return memoizedParams
    }

    public func retExprIsEmpty(retExpr: ReturnExpr): Bool {
        var throwable = None<Exception>
        try {
            retExpr.expr
        } catch (e: Exception) {
            throwable = e
        } finally {
            if (let Some(_) <- throwable) {
                return false
            } else {
                return true
            }
        }
        return true
    }
}

class MemoFuncVisitor <: MemoVisitor {
    var count = 0

    init(memoizedParamsNames: ArrayList<String>) {
        this.memoizedParamsNames = memoizedParamsNames
    }

    public override func visit(funcDecl: FuncDecl) {
        let funcType = funcDecl.declType
        let blockNodes = funcDecl.block.nodes
        let memoizedParams = memoizeParams(funcDecl)

        funcDecl.block.nodes = ArrayList()
        funcDecl.block.nodes.add(VarDecl(quote(let __memo_key = getCallsiteKey())))
        funcDecl.block.nodes.add(
            VarDecl(
            quote(let __memo_scope = getMemoScope < $(funcType) >(__memo_key, $(memoizedParams.size)))
        ))
        
        for (memoizedParam in memoizedParams) {
            funcDecl.block.nodes.add(memoizedParam)
        }
        for (param in memoizedParamsNames) {
            let varGetterName = Token(IDENTIFIER, "__memo_param_value_" + param)
            let memoParam = Token(IDENTIFIER, "__memo_param_" + param)
            let varGetter = VarDecl(quote(let $(varGetterName) = $(memoParam).getValue()))
            funcDecl.block.nodes.add(varGetter)
        }
        funcDecl.block.nodes.add(
            IfExpr(
            quote(if (__memo_scope.isUnchanged()) {
                        return __memo_scope.getCached()
                    })
            )
        )
        for (blockNode in blockNodes) {
            blockNode.traverse(LambdaVisitor(this.memoizedParamsNames))
            blockNode.traverse(RefExprVisitor(this.memoizedParamsNames))
            blockNode.traverse(ReturnVisitor())
            funcDecl.block.nodes.add(blockNode)
        }
        let lastNode = funcDecl.block.nodes[funcDecl.block.nodes.size - 1]
        if (!(lastNode is ReturnExpr) && quote($(funcType)).toTokens()[0].kind == Token(UNIT).kind) {
            funcDecl.block.nodes.add(parseExpr(quote(return __memo_scope.recache(MEMO_UNIT))))
        }
        breakTraverse()
    }
}

class LambdaVisitor <: MemoVisitor {
    init(memoizedParamsNames: ArrayList<String>) {
        this.memoizedParamsNames = memoizedParamsNames
    }

    public override func visit(lambdaExpr: LambdaExpr) {
        let blockNodes = lambdaExpr.nodes
        lambdaExpr.nodes = ArrayList()

        for (param in memoizedParamsNames) {
            let varGetterName = Token(IDENTIFIER, "__memo_param_value_" + param)
            let memoParam = Token(IDENTIFIER, "__memo_param_" + param)
            let varGetter = VarDecl(quote(let $(varGetterName) = $(memoParam).getValue()))
            lambdaExpr.nodes.add(varGetter)
        }
        for (blockNode in blockNodes) {
            blockNode.traverse(RefExprVisitor(memoizedParamsNames))
            lambdaExpr.nodes.add(blockNode)
        }
        // let lastNode = lambdaExpr.nodes[lambdaExpr.nodes.size - 1]
        // if (!(lastNode is ReturnExpr)) {
        //     lambdaExpr.nodes.add(parseExpr(quote(return)))
        // }
        // breakTraverse()
    }
}

class MemoLambdaVisitor <: MemoVisitor {
    var inFunctionCall: Bool = false

    init(memoizedParamsNames: ArrayList<String>) {
        this.memoizedParamsNames = memoizedParamsNames
    }
    init(memoizedParamsNames: ArrayList<String>, inFunctionCall: Bool) {
        this.memoizedParamsNames = memoizedParamsNames
        this.inFunctionCall = inFunctionCall
    }

    public override func visit(lambdaExpr: LambdaExpr) {
        let memoizedParams = memoizeParams(lambdaExpr)
        let blockNodes = lambdaExpr.nodes
        lambdaExpr.nodes = ArrayList()

        lambdaExpr.nodes.add(VarDecl(quote(let __memo_key = getCallsiteKey())))
        lambdaExpr.nodes.add(
            VarDecl(
            quote(let __memo_scope = getMemoScope < Unit >(__memo_key, $(memoizedParams.size)))
            ))
            
        for (memoizedParam in memoizedParams) {
            lambdaExpr.nodes.add(memoizedParam)
        }
        for (param in memoizedParamsNames) {
            let varGetterName = Token(IDENTIFIER, "__memo_param_value_" + param)
            let memoParam = Token(IDENTIFIER, "__memo_param_" + param)
            let varGetter = VarDecl(quote(let $(varGetterName) = $(memoParam).getValue()))
            lambdaExpr.nodes.add(varGetter)
        }
        lambdaExpr.nodes.add(
            IfExpr(
            quote(if (__memo_scope.isUnchanged()) {
                        return __memo_scope.getCached()
                    })
        ))
        for (blockNode in blockNodes) {
            blockNode.traverse(LambdaVisitor(this.memoizedParamsNames))
            blockNode.traverse(RefExprVisitor(this.memoizedParamsNames))
            blockNode.traverse(ReturnVisitor())
            lambdaExpr.nodes.add(blockNode)
        }
        let lastNode = lambdaExpr.nodes[lambdaExpr.nodes.size - 1]
        if (!(lastNode is ReturnExpr)) {
            lambdaExpr.nodes.add(parseExpr(quote(return __memo_scope.recache(MEMO_UNIT))))
        }
        breakTraverse()
    }
}

func modifyFunction(input: Tokens): Tokens {
    var funcDecl = parseDecl(input, astKind: "FUNC") as FuncDecl
    var existingFuncDecl = if (let Some(funcDecl) <- funcDecl) {
        funcDecl
    } else {
        throw IllegalArgumentException()
    }

    let visitor = MemoFuncVisitor(ArrayList())
    existingFuncDecl.traverse(visitor)
    return existingFuncDecl.toTokens()
}

func modifyLambda(input: Tokens): Tokens {
    var lambdaExpr = parseExpr(input) as LambdaExpr
    var existingLambdaExpr = if (let Some(lambdaExpr) <- lambdaExpr) {
        lambdaExpr
    } else {
        throw IllegalArgumentException()
    }

    let visitor = MemoLambdaVisitor(ArrayList())
    existingLambdaExpr.traverse(visitor)
    return existingLambdaExpr.toTokens()
}

func modifyTrailingLambda(input: Tokens): Tokens {
    var lambdify = Token(LCURL) + input + Token(RCURL)
    var output = Tokens()
    for(token in modifyLambda(lambdify).toTokens()) {
        output.append(token)
    }
    output.remove(0)
    output.remove(output.size-1)
    return output
}

public macro Memo(input: Tokens): Tokens {
    let firstToken = input.toTokens()[0]
    let memoFunction = Token(FUNC).kind
    let memoLambda = Token(LCURL).kind
    let memoTrailingLambda = Token(IDENTIFIER).kind

    var output = Tokens()
    if(firstToken.kind == memoFunction) {
        output = modifyFunction(input)
        // println(quote($(output)))
    }
    if(firstToken.kind == memoLambda) {
        output = modifyLambda(input)
        // println(quote($(output)))
    }
    if(firstToken.kind != memoLambda && firstToken.kind != memoFunction) {
        output = modifyTrailingLambda(input)
        // println(quote($(output)))
    }

    return output
}
