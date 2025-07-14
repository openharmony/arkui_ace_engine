
import { ManyImportComponent152 } from "./manyImportFile152"
import { ManyImportComponent153 } from "./manyImportFile153"


@Component
export struct ManyImportComponent76 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent152()
            ManyImportComponent153()

        }
    }
}
