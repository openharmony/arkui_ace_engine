/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package KoalaRuntime.macrotest

import KoalaRuntime.memoize.*

import std.ast.*
import std.math.*

func areEqual(example: Tokens, golden: Tokens): Bool {
    var exampleWithoutNL = Tokens()
    var goldenWithoutNL = Tokens()
    for (i in 0..example.size - 1) {
        if (example[i].kind != Token(NL).kind) {
            exampleWithoutNL.append(example[i])
        }
    }
    for (i in 0..golden.size - 1) {
        if (golden[i].kind != Token(NL).kind) {
            goldenWithoutNL.append(golden[i])
        }
    }
    var i = 0
    if (exampleWithoutNL.size != goldenWithoutNL.size) {
        return false
    } else {
        while (i < exampleWithoutNL.size) {
            if (exampleWithoutNL[i].kind != goldenWithoutNL[i].kind) {
                return false
            }
            i = i + 1
        }
    }
    return true
}

@Test
public class FunctionTest {
    @TestCase
    public func functionWithNoArgs(): Unit {
        // TODO: remove embedding lambda
        let example = quote($({ =>
            @Memo(func f(): Unit {
                return
            })}))
        let golden = quote(
            { =>
                func f ( ) : Unit { 
                    let __memo_key = getCallsiteKey ( ) 
                    let __memo_scope = getMemoScope < Unit > ( __memo_key , 0 ) 
                    if ( __memo_scope . isUnchanged ( ) ) { 
                        return __memo_scope . getCached ( ) 
                    } 
                    return  __memo_scope.recache ( MEMO_UNIT )
                }
            })
        @Assert(areEqual(example, golden))
    }
    @TestCase
    public func functionSquare(): Unit {
        // TODO: remove embedding lambda
        let example = quote($({ =>
            @Memo(func square(x: Int64): Int64 {
                return x * x
            })}))
        let golden = quote(
            { =>
                func square ( x : Int64 ) : Int64 { 
                    let __memo_key = getCallsiteKey ( )  
                    let __memo_scope = getMemoScope < Int64 > ( __memo_key , 1 ) 
                    let __memo_param_x = getParameter ( __memo_scope , 0 , x , "x" ) 
                    let __memo_param_value_x = __memo_param_x . getValue ( ) 
                    if ( __memo_scope . isUnchanged ( ) ) {
                        return __memo_scope . getCached ( ) 
                    } 
                    return __memo_scope.recache ( __memo_param_value_x * __memo_param_value_x ) 
                } 
            })
        @Assert(areEqual(example, golden))
    }
    @TestCase
    public func memoAndNonMemoArg(): Unit {
        // TODO: remove embedding lambda
        let example = quote($({ =>
            @Memo(func foo(x: Int64): Int64 {
                let y = 0
                return x + y
            })}))
        let golden = quote(
            { =>
                func foo ( x : Int64 ) : Int64 { 
                    let __memo_key = getCallsiteKey ( )
                    let __memo_scope = getMemoScope < Int64 > ( __memo_key , 1 ) 
                    let __memo_param_x = getParameter ( __memo_scope , 0 , x , "x" ) 
                    let __memo_param_value_x = __memo_param_x . getValue ( ) 
                    if ( __memo_scope . isUnchanged ( ) ) { 
                        return __memo_scope . getCached ( ) 
                    } 
                    let y = 0 
                    return __memo_scope . recache ( __memo_param_value_x + y ) 
                } 
            })
        @Assert(areEqual(example, golden))
    }
}

// TODO: non-Unit return type lambda
@Test
public class LambdaExprTest {
    @TestCase
    public func emptyLambda(): Unit {
        let example = quote($(@Memo({=>})))
        let golden = quote(
            { =>
                let __memo_key = getCallsiteKey ( )
                let __memo_scope = getMemoScope < Unit > ( __memo_key , 0 )
                if ( __memo_scope . isUnchanged ( ) ) { 
                    return __memo_scope . getCached ( ) 
                }
                return __memo_scope . recache ( MEMO_UNIT )
            })
        @Assert(areEqual(example, golden))
    }
    @TestCase
    public func lambdaOneArg(): Unit {
        let example = quote($(@Memo({x: Int64=>})))
        let golden = quote(
            { x : Int64 =>
                let __memo_key = getCallsiteKey ( )
                let __memo_scope = getMemoScope < Unit > ( __memo_key , 1 )
                let __memo_param_x = getParameter ( __memo_scope , 0 , x , "x" )
                let __memo_param_value_x = __memo_param_x . getValue ( )
                if ( __memo_scope . isUnchanged ( ) ) { 
                    return __memo_scope . getCached ( ) 
                }
                return __memo_scope . recache ( MEMO_UNIT )
                })
        @Assert(areEqual(example, golden))
    }
}

@Test
public class trailingLambdaTest {
    @TestCase
    public func emptyTrailingLambda(): Unit {
        let example = quote($(f() { @Memo( =>
                return
            )}
        ))
        let golden = quote(
            f ( ) {=>
                let __memo_key = getCallsiteKey ( )  
                let __memo_scope = getMemoScope < Unit > ( __memo_key , 0 )  
                if ( __memo_scope . isUnchanged ( ) ) { 
                    return __memo_scope . getCached ( )
                }  
                return __memo_scope . recache ( MEMO_UNIT )
            })
        @Assert(areEqual(example, golden))
    }
    @TestCase
    public func nonEmptyTralingLambda(): Unit {
        let example = quote($(f() { @Memo(x: Int64 =>
                let y = x
                return
            )}
        ))
        let golden = quote(
            f ( ) {x : Int64 =>
                let __memo_key = getCallsiteKey ( )  
                let __memo_scope = getMemoScope < Unit > ( __memo_key , 1 )  
                let __memo_param_x = getParameter ( __memo_scope , 0 , x , "x" )  
                let __memo_param_value_x = __memo_param_x . getValue ( )  
                if ( __memo_scope . isUnchanged ( ) ) {  
                    return __memo_scope . getCached ( ) 
                }  
                let y = __memo_param_value_x  
                return __memo_scope . recache ( MEMO_UNIT )
            })
        @Assert(areEqual(example, golden))
    }
}

@Test
public class memoComposition {
    @TestCase
    public func lambdaInsideFunction(): Unit {
        let example = quote($({ => @Memo
            func foo(x: Int64): Unit {
                let t = 0
                bar(@Memo({y: Int64=>
                    let z = x + y + t
                    return
                }))
                return
            }
        }))
        let golden = quote(
            { =>
                func foo ( x : Int64 ) : Unit { 
                    let __memo_key = getCallsiteKey ( ) 
                    let __memo_scope = getMemoScope < Unit > ( __memo_key , 1 ) 
                    let __memo_param_x = getParameter ( __memo_scope , 0 , x , "x" ) 
                    let __memo_param_value_x = __memo_param_x . getValue ( ) 
                    if ( __memo_scope . isUnchanged ( ) ) { 
                        return __memo_scope . getCached ( ) 
                    } 
                    let t = 0 
                    bar ( { y : Int64 =>
                        let __memo_param_value_x = __memo_param_x . getValue ( )  
                        let __memo_key = getCallsiteKey ( )  
                        let __memo_scope = getMemoScope < Unit > ( __memo_key , 1 )  
                        let __memo_param_y = getParameter ( __memo_scope , 0 , y , "y" )  
                        let __memo_param_value_y = __memo_param_y . getValue ( )  
                        if ( __memo_scope . isUnchanged ( ) ) { 
                            return __memo_scope . getCached ( ) 
                        }  
                        let z = __memo_param_value_x + __memo_param_value_y + t  
                        return __memo_scope . recache ( MEMO_UNIT ) 
                    } ) 
                    return __memo_scope . recache ( MEMO_UNIT ) 
                } 
            })
        @Assert(areEqual(example, golden))
    }
}
