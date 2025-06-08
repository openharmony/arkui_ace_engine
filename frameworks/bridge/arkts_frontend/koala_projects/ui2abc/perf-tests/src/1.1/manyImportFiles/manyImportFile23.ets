
import { ManyImportComponent46 } from "./manyImportFile46"
import { ManyImportComponent47 } from "./manyImportFile47"


@Component
export struct ManyImportComponent23 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent46()
            ManyImportComponent47()

        }
    }
}
