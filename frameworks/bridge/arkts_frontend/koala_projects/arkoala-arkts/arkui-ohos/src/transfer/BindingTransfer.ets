import {
  InteropTransferMutableBinding,
  InteropTransferBinding,
} from '../stateManagement/interop/interopBinding';
import { MutableBinding, Binding} from '../stateManagement';

export class MutableBindingTransfer {
  static transferStatic(input: Any): Object {
    if (typeof input !== 'object' || input === null) {
      throw Error(
        'MutableBindingTransfer.transferStatic: input must be a non-null object.',
      );
    }
    const dynBinding = ESValue.wrap(input);
    const transferMutableBinding = new InteropTransferMutableBinding<Any>(
      dynBinding,
    );
    return transferMutableBinding;
  }

  static transferDynamic(input: Object): Any {
    const mutablebinding = input as MutableBinding<Any>;
    const global = ESValue.getGlobal();
    const getter = (reflect.Value.of(mutablebinding) as ClassValue).getFieldByName('getter_').getData() as Object;
    const setter = (reflect.Value.of(mutablebinding) as ClassValue).getFieldByName('setter_').getData() as Object;
    return global.getProperty('createMutableBinding').invoke(ESValue.wrap(getter), ESValue.wrap(setter)).unwrap();
  }
}

export class BindingTransfer {
  static transferStatic(input: Any): Object {
    if (typeof input !== 'object' || input === null) {
      throw Error(
        'MutableBindingTransfer.transferStatic: input must be a non-null object.',
      );
    }
    const dynBinding = ESValue.wrap(input);
    const transferBinding = new InteropTransferBinding<Any>(dynBinding);
    return transferBinding;
  }

  static transferDynamic(input: Object): Any {
    const binding = input as Binding<Any>;
    const global = ESValue.getGlobal();
    const getter = (reflect.Value.of(binding) as ClassValue).getFieldByName('getter_').getData() as Object;
    return global.getProperty('createBinding').invoke(ESValue.wrap(getter)).unwrap();
  }
}
