
import { ManyImportComponent82 } from "./manyImportFile82"
import { ManyImportComponent83 } from "./manyImportFile83"


@Component
export struct ManyImportComponent41 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent82()
            ManyImportComponent83()

        }
    }
}
