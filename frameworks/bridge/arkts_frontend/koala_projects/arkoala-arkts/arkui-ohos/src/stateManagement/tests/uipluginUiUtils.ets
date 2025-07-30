import { UIUtilsInternal, UIUtils } from 'stateManagement/sdk/uiutils'
import { IObservedObject } from 'stateManagement/interface/iObservedObject'
import { __StateMgmtFactoryImpl } from 'stateManagement/base/stateMgmtFactory.ets'

import { IObservedObject } from 'stateManagement/interface/iObservedObject'
import { stateMgmtConsole } from 'stateManagement/tools/stateMgmtConsoleTrace';

// unit testing
import { tsuite, tcase, test, eq, not_eq } from 'stateManagement/utest/lib/testFramework'
import { UIUtilsPlugin, UIUtils } from '../../sdk/uiutils.ets';



class ObservedData implements IObservedObject {
    setV1RenderId(renderId: double): void {}
    addWatchSubscriber(watchId: double): void {}
    removeWatchSubscriber(watchId: double): boolean {return false}
}

type CustomObservedData = ObservedData

interface testInt {
    propA: Double;
    propB: string;
}


/*
UIPlugin
@ObservedV2 class object           => unmodified input object
@Observe (V1) with/without @Track  => unmodified input object
Regular/plain class                => unmodified input object
Simple type variable               => unmodified variable

Anonymous class of interface type  => Object wrapped inside a proxy
Array                              => WrappedArray
Set                                => WrappedSet
Map                                => WrappedMap
Date                               => WrappedDate

type MyTypeSimple = number
type MyTypeClass  = NonObservedClass
*/



export function run_makeobserved() : Boolean {

    const tests = tsuite("UIUtils tests", () => {
      stateMgmtConsole.log(`run make observed mix =======================`);
  
    tcase("Test 1: makeObserved for Array ", () => {
        const arrPure : Array<number> = [ 1, 2, 3]
        let arrWrapped1 = UIUtilsPlugin.makeObservedArray(arrPure)
        let arrWrapped2 = UIUtilsPlugin.makeObservedArray(arrPure)
        test("Compare wrapped arrays", eq(arrWrapped1, arrWrapped2));
        test("Compare un-wrapped array1", eq(UIUtils.getTarget(arrWrapped1), arrPure));
        test("Compare un-wrapped array2", eq(UIUtils.getTarget(arrWrapped2), arrPure));
        test("Compare wrapped arrays", eq(UIUtils.getTarget(arrWrapped1), UIUtils.getTarget(arrWrapped2)));
        test("Compare un-wrapped and wrapped array1 ", not_eq(UIUtils.getTarget(arrWrapped1), arrWrapped1));
        test("Compare un-wrapped and wrapped array2", not_eq(UIUtils.getTarget(arrWrapped2), arrWrapped2));
    })

    tcase("Test 2: makeObserved for Map", () => {
        const mapPure : Map<string,boolean> =
            new Map<string, boolean>([["James", false], ["Jane", true], ["Doe", false]])
        let mapWrapped1 = UIUtilsPlugin.makeObservedMap(mapPure)
        let mapWrapped2 = UIUtilsPlugin.makeObservedMap(mapPure)
    
        test("Compare wrapped maps", eq(mapWrapped1, mapWrapped2));
        test("Compare un-wrapped map1", eq(UIUtils.getTarget(mapWrapped1), mapPure));
        test("Compare un-wrapped map2", eq(UIUtils.getTarget(mapWrapped2), mapPure));
        test("Compare wrapped maps", eq(UIUtils.getTarget(mapWrapped1), UIUtils.getTarget(mapWrapped2)));
        test("Compare un-wrapped and wrapped maps1 ", not_eq(UIUtils.getTarget(mapWrapped1), mapWrapped1));
        test("Compare un-wrapped and wrapped maps2", not_eq(UIUtils.getTarget(mapWrapped2), mapWrapped2));
    })

    tcase("Test 3: makeObserved for Set", () => {
        const setPure : Set<string> =
            new Set<string>(["James", "Jane", "Doe"]);
        let setWrapped1 = UIUtilsPlugin.makeObservedSet(setPure)
        let setWrapped2 = UIUtilsPlugin.makeObservedSet(setPure)

        test("Compare wrapped maps", eq(setWrapped1, setWrapped2));
        test("Compare un-wrapped map1", eq(UIUtils.getTarget(setWrapped1), setPure));
        test("Compare un-wrapped map2", eq(UIUtils.getTarget(setWrapped2), setPure));
        test("Compare wrapped maps", eq(UIUtils.getTarget(setWrapped1), UIUtils.getTarget(setWrapped2)));
        test("Compare un-wrapped and wrapped maps1 ", not_eq(UIUtils.getTarget(setWrapped1), setWrapped1));
        test("Compare un-wrapped and wrapped maps2", not_eq(UIUtils.getTarget(setWrapped2), setWrapped2));
    })
 
    tcase("Test 4: makeObserved for Date", () => {
        const datePure : Date = new Date()
        let dateWrapped1 = UIUtilsPlugin.makeObservedDate(datePure)
        let dateWrapped2 = UIUtilsPlugin.makeObservedDate(datePure)

        test("Compare wrapped dates", eq(dateWrapped1, dateWrapped2));
        test("Compare un-wrapped date1", eq(UIUtils.getTarget(dateWrapped1), datePure));
        test("Compare un-wrapped date2", eq(UIUtils.getTarget(dateWrapped2), datePure));
        test("Compare wrapped dates", eq(UIUtils.getTarget(dateWrapped1), UIUtils.getTarget(dateWrapped2)));
        test("Compare un-wrapped and wrapped date1 ", not_eq(UIUtils.getTarget(dateWrapped1), dateWrapped1));
        test("Compare un-wrapped and wrapped date2", not_eq(UIUtils.getTarget(dateWrapped2), dateWrapped2));
      
    })

    tcase("Test 5: makeObserved for Interface ObjectLiterals", () => {
        const ifObjectLiteral: testInt = {propA: 111, propB: "hello"} as testInt;
        let ifObjectLiteralWrapped1 = UIUtils.makeObserved(ifObjectLiteral)
        let ifObjectLiteralWrapped2 = UIUtils.makeObserved(ifObjectLiteral)
        let ifObjectLiteralWrapped3 = UIUtils.makeObserved(ifObjectLiteralWrapped2)
        test("Compare proxied Interface ObjectLiterals 1-2", eq(ifObjectLiteralWrapped1, ifObjectLiteralWrapped2));
        test("Compare proxied Interface ObjectLiterals 2-3", eq(ifObjectLiteralWrapped2, ifObjectLiteralWrapped3));
        test("Compare proxied Interface ObjectLiterals 1-3", eq(ifObjectLiteralWrapped1, ifObjectLiteralWrapped3));
        test("Compare proxied Interface ObjectLiterals orig-wrapped1", eq(ifObjectLiteral, UIUtils.getTarget(ifObjectLiteralWrapped1)));
        test("Compare proxied Interface ObjectLiterals orig-wrapped1", eq(ifObjectLiteral, UIUtils.getTarget(ifObjectLiteralWrapped2)));
        test("Compare proxied Interface ObjectLiterals orig-wrapped1", eq(ifObjectLiteral, UIUtils.getTarget(ifObjectLiteralWrapped3)));
        test("Compare proxied Interface ObjectLiterals orig-orig", eq(ifObjectLiteral, UIUtils.getTarget(ifObjectLiteral)));

        const ifObjectLiteralB: testInt = {propA: 111, propB: "hello"} as testInt;
        let ifObjectLiteralWrappedB1 = UIUtils.makeObserved(ifObjectLiteralB)
        test("Compare proxied Interface ObjectLiterals 1-B1", not_eq(ifObjectLiteralWrapped1, ifObjectLiteralWrappedB1));
        test("Compare proxied Interface ObjectLiterals orig-origB", not_eq(ifObjectLiteralB, ifObjectLiteral));
    })

    tcase("Test 6: makeObservedVersatile for Array ", () => {
        const arrPure : Array<string|number> = [ 1, "hello", 3]
        let arrWrapped1 = UIUtils.makeObserved(arrPure)
        let arrWrapped2 = UIUtils.makeObserved(arrPure)
        test("Compare wrapped arrays", eq(arrWrapped1, arrWrapped2));
        test("Compare un-wrapped array1", eq(UIUtils.getTarget(arrWrapped1), arrPure));
        test("Compare un-wrapped array2", eq(UIUtils.getTarget(arrWrapped2), arrPure));
        test("Compare wrapped arrays", eq(UIUtils.getTarget(arrWrapped1), UIUtils.getTarget(arrWrapped2)));
        test("Compare un-wrapped and wrapped array1 ", not_eq(UIUtils.getTarget(arrWrapped1), arrWrapped1));
        test("Compare un-wrapped and wrapped array2", not_eq(UIUtils.getTarget(arrWrapped2), arrWrapped2));
        console.log("Wrapped Element 0 " + arrWrapped1[0])
        console.log("Wrapped Element 1 " + arrWrapped1[1])
        console.log("Wrapped Element 2 " + arrWrapped1[2])
    })

    tcase("Test 7: UIUtils.makeObserved public  for Map", () => {
        const mapPure : Map<string,boolean> =
            new Map<string, boolean>([["James", false], ["Jane", true], ["Doe", false]])
        console.log("=============== UIUtils.makeObservedVersatile(mapPure)")
        let mapWrapped1 = UIUtils.makeObserved(mapPure)
        console.log("=============== UIUtils.makeObservedVersatile(mapPure)")
        let mapWrapped2 = UIUtils.makeObserved(mapPure)
        test("Compare wrapped maps", eq(mapWrapped1, mapWrapped2));
        test("Compare un-wrapped map1", eq(UIUtils.getTarget(mapWrapped1), mapPure));
        test("Compare un-wrapped map2", eq(UIUtils.getTarget(mapWrapped2), mapPure));
        test("Compare wrapped maps", eq(UIUtils.getTarget(mapWrapped1), UIUtils.getTarget(mapWrapped2)));
        test("Compare un-wrapped and wrapped maps1 ", not_eq(UIUtils.getTarget(mapWrapped1), mapWrapped1));
        test("Compare un-wrapped and wrapped maps2", not_eq(UIUtils.getTarget(mapWrapped2), mapWrapped2));
    })

    });
 
    tests();
    return true;

}


export function run_makeobserved_short() : Boolean {

        const tests = tsuite("UIUtils tests", () => {
          stateMgmtConsole.log(`run make observed mix =======================`);
      
          tcase("Test 5: makeObserved for Interface ObjectLiterals", () => {
            const ifObjectLiteral: testInt = {propA: 111, propB: "hello"} as testInt;
            let ifObjectLiteralWrapped1 = UIUtils.makeObserved(ifObjectLiteral)
            let ifObjectLiteralWrapped2 = UIUtils.makeObserved(ifObjectLiteral)
            let ifObjectLiteralWrapped3 = UIUtils.makeObserved(ifObjectLiteralWrapped2)
            test("Compare proxied Interface ObjectLiterals 1-2", eq(ifObjectLiteralWrapped1, ifObjectLiteralWrapped2));
            test("Compare proxied Interface ObjectLiterals 2-3", eq(ifObjectLiteralWrapped2, ifObjectLiteralWrapped3));
            test("Compare proxied Interface ObjectLiterals 1-3", eq(ifObjectLiteralWrapped1, ifObjectLiteralWrapped3));
            test("Compare proxied Interface ObjectLiterals orig-wrapped1", eq(ifObjectLiteral, UIUtils.getTarget(ifObjectLiteralWrapped1)));
            test("Compare proxied Interface ObjectLiterals orig-wrapped1", eq(ifObjectLiteral, UIUtils.getTarget(ifObjectLiteralWrapped2)));
            test("Compare proxied Interface ObjectLiterals orig-wrapped1", eq(ifObjectLiteral, UIUtils.getTarget(ifObjectLiteralWrapped3)));
            test("Compare proxied Interface ObjectLiterals orig-orig", eq(ifObjectLiteral, UIUtils.getTarget(ifObjectLiteral)));
            const ifObjectLiteralB: testInt = {propA: 111., propB: "hello"} as testInt;
            let ifObjectLiteralWrappedB1 = UIUtils.makeObserved(ifObjectLiteralB)
            test("Compare proxied Interface ObjectLiterals 1-B1", not_eq(ifObjectLiteralWrapped1, ifObjectLiteralWrappedB1));
            test("Compare proxied Interface ObjectLiterals orig-origB", not_eq(ifObjectLiteralB, ifObjectLiteral));
            test("Compare original value 111", eq(ifObjectLiteralB.propA, 111.));
            test("Compare proxied value 111", eq(ifObjectLiteralWrappedB1.propA, 111.));
        })
    

    });
 
    tests();
    return true;
  
  }
  
