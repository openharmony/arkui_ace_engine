
function main() {}


function someFunc(value: SomeClass | undefined) {
  let x: SomeClass | undefined = value;
  let zzz = ({let chaintmp%%_0 = x;
  (((chaintmp%%_0) === (undefined)) ? undefined : chaintmp%%_0.y)});
}


class SomeClass {
  public y: string = "yyy";
  
  public constructor() {}
  
}

