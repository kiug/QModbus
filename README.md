# QModbus

QModbus is a Qt/C++ wrapper around [libmodbus](https://libmodbus.org/) that
provides an object-oriented, Qt-style API for Modbus communication. It lets a
Qt application act as a Modbus **master** over TCP, RTU, or TCP-PI and exchange
coils, discrete inputs, and holding/input registers.

## Features

- Modbus **master** over:
  - Modbus/TCP (`QModbusMaster("127.0.0.1", 502)`)
  - Modbus/RTU (serial, with baud/parity/data/stop bits)
  - Modbus/TCP-PI (IPv4/IPv6 node + service)
- Typed access to registers and bits:
  - `QModbusRegisters` — signed/unsigned 16/32/64-bit integers and
    `float`/`double`, encoded in standard Modbus **big-endian** (`abcd`) order.
  - `QModbusBits` — coils and discrete inputs.
  - `QModbusError` — `isValid()` / `message()` error reporting.
- Qt-style error handling via a per-object last-error state.

## Requirements

- Qt 5.12 or later (Core; Widgets/Gui only for the GUI app, Test only for tests)
- libmodbus 3.1.x or later (LGPL-2.1+)
- A C++11 toolchain (tested with MinGW-w64 7.3)

## Building

The project uses qmake. The dependency paths are configured through qmake
feature files (`.prf`), which contain absolute paths that you must adjust to
your machine.

1. Copy the feature file into your Qt `mkspecs/features` directory and edit the
   library path inside it, for example:

   ```sh
   cp libmodbus-3.1.10.prf $QTDIR/5.12.12/mingw73_32/mkspecs/features/
   ```

   and set `LIB_DIR` in that file to your libmodbus installation.

2. Build the library:

   ```sh
   qmake QModbus.pro
   make        # or mingw32-make / nmake on Windows
   ```

3. Build the GUI app (optional):

   ```sh
   qmake QModbusMasterGUI.pro
   make
   ```

4. Build and run the tests (optional):

   ```sh
   qmake QModbusTest.pro
   make
   ```

## Usage

```cpp
#include <QDebug>
#include "qmodbusmaster.h"
#include "qmodbusregisters.h"

using namespace Modbus;

QModbusMaster master("127.0.0.1", 502);
master.connect();

QModbusRegisters regs(0, 4);   // start address 0, 4 registers
if (master.readRegisters(regs)) {
    qDebug() << regs.getInteger32(0)
             << regs.getFloat32(0);
} else {
    qDebug() << master.lastError().message();
}

master.close();
```

## API overview

- `QModbusMaster` — connect/close/flush, `setSlave()`, `setBroadcast()`,
  `readBits()`/`readInputBits()`/`readRegisters()`/`readInputRegisters()`,
  `writeBit()`/`writeBits()`/`writeRegister()`/`writeRegisters()`, and
  `writeAndReadRegisters()`, plus timeout/debug/error-recovery settings.
- `QModbusRegisters` — `getValue()`/`setValue()` and typed accessors:
  `getInteger16/32/64`, `getUInteger16/32/64`, `getFloat32/64` (with matching
  `set*` methods).
- `QModbusBits` — `getValue()`/`setValue()` for individual bits.
- `QModbusError` — `isValid()` and `message()`.

## Byte order

32- and 64-bit values are written to the Modbus wire in **big-endian** (`abcd`)
word order, as required by the Modbus specification, independently of the host
CPU endianness. If a device uses a non-standard word order, swap the data
before/after calling the accessors.

## Testing

Unit tests (`TestQModbusBits`, `TestQModbusRegisters`, `TestQModbusError`) run
standalone. The integration tests (`TestQModbusMaster`) need a Modbus server at
`127.0.0.1:502`; you can use `diagslave`:

```sh
diagslave -m tcp -p 502 &
QModbusTest.exe
```

## License

QModbus is licensed under the GNU Lesser General Public License, version 3 or
later (LGPL-3.0-or-later). See [LICENSE.txt](LICENSE.txt).

Third-party components and their licenses are listed in
[THIRD-PARTY-NOTICES.txt](THIRD-PARTY-NOTICES.txt).
