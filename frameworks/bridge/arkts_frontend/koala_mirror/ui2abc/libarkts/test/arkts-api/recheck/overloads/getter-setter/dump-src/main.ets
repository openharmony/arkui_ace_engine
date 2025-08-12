
function main() {}



interface I {
  get f(): ((createdParam: boolean)=> void)
  
  set f(f: ((createdParam: boolean)=> void))
  
}

