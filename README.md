# [PHY6222](https://doc.soc.xin/PHY6222)

* [phyplus](http://www.phyplusinc.com): [Cortex-M0](https://github.com/SoCXin/Cortex)
* [L2R2](https://github.com/SoCXin/Level): 96 MHz

## [简介](https://github.com/SoCXin/PHY6222/wiki)

[PHY6222](https://github.com/SoCXin/PHY6222) 内置的高性能多模射频收发机最大发射功率达到10dBm，BLE 1Mbps速率下接收灵敏度-99dBm，BLE 125Kbps速率下接收灵敏度-105dBm，同时提供3dB的解调增益；超低功耗芯片架构使得休眠电流低至0.3uA，峰值收发功耗4.6/4mA，多场景平均应用功耗<10uA，保证常规200mAH的纽扣电池正常供电状态下能够持续工作5年以上。接口资源丰富，拥有超过20个GPIO接口。

拥有基于Bluetooth LE 5.2的自主知识产权全栈蓝牙方案，支持包括SIG-Mesh全角色组网、AoA/AoD无线定位、2Mbps高速率模式、BLE长距离模式、主从配对一主多从、扩展广播/周期广播在内的主流BLE功能。支持自主知识产权的多协议栈：Matter (Bluetooth LE+Zigbee) 多协议共存；PhyPlus私有2.4GHz协议栈。

### 关键参数

* 96 MHz Cortex-M0 (<60uA/MHz)
* 64KB SRAM + 96KB ROM + 256bit efuse
* 可选128KB-8M FLASH
* 多协议支持 Matter BLE+ZigBee
* 工作电压：1.8V-3.6V
* QFN32: 22x GPIO


## [资源收录](https://github.com/SoCXin)

* [参考资源](src/)
* [参考文档](docs/)
* [参考工程](project/)

## [选型建议](https://github.com/SoCXin/PHY6222)

[PHY6222](https://github.com/SoCXin/PHY6222) 是涂鸦蓝牙模组 [BP系列](https://developer.tuya.com/cn/docs/iot/BP3L-module-datasheet?id=Kaprpg4fdjsjz) 的主控芯片

相对于QFN32封装的PHY6222，工业场景也可选SSOP24封装的[PHY6252](http://wiki.phyplusinc.com/doku.php?id=menu:phy62_series:phy6252)

## [www.SoC.xin](http://www.SoC.Xin)
