export class Utils {
    static begin_: (str:string) => void = (str: string)=> {
    };
    static end_: () => void = () =>{
    };

    static Init(begin:(str:string) => void, end:() => void) {
        Utils.begin_ = begin;
        Utils.end_ = end;
    }

    static traceBegin(str:string):void {
        Utils.begin_(str);
    }
    static traceEnd(): void {
        Utils.end_();
    }
};