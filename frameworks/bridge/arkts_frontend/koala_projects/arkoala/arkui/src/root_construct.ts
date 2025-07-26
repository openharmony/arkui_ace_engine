import { ArkRootPeer } from "./generated/peers/ArkStaticComponentsPeer"
import { setRootConstruct } from "@koalaui/arkoala"

setRootConstruct(() => ArkRootPeer.create())