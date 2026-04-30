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
    return global.getProperty('createMutableBinding').invoke(
      ESValue.wrap(mutablebinding.getter), ESValue.wrap(mutablebinding.setter)).unwrap();
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
    return global.getProperty('createBinding').invoke(ESValue.wrap(binding.getter)).unwrap();
  }
}
