# twoday-recruitment-case
## Assumptions
The main assumption I've made is that point of the exercise was writing the logic, tests, and dealing with flexible requirements. Not setting up a database, UI, or CLI. As such, the tests can be seen as examples of how to use the system.

## Structure
I started by thinking about how I would want users of the system to be able to use it. I imagined a scenario where the backend receives some data from a web form and shuttles it to the parking system.
### Pseudo-code of System Usage
```python
ui = GetUiHandle()
database = Database(IParkingDataBroker)
houseInfo = DefaultHouseInfo()
parkingHouse = ParkingHouse(houseInfo, database)

def OnEntryRequest(entryDetails):
	entryResult = parkingHouse.ProcessEntry(entryDetails)
	if entryResult.isValid:
		ui.OnSucessfulEntry()
	else:
		ui.OnNewEntryError(entryResult.errorType)

def OnExitRequest(exitDetails):
	exitResult = parkingHouse.ProcessExit(exitDetails)
	if exitResult.isValid:
		ui.OnSucessfulExit(exitResult.cost)
	else:
		ui.OnNewExitError(exitResult.errorType)
```
I then wrote more pseudo-code about how things would work internally, and from that I ended up with the following structure:

![diagram](readme_attachments/loose-class-diagram.svg)


## Build Instructions
Clone this repo and follow the steps for your OS.
### Linux
Make sure you have git, CMake, and make installed on your system, then copy this into your terminal if you're using bash, otherwise do it line by line.

```bash
    git clone https://github.com/Clover83/twoday-recruitment-case.git && \
    cd twoday-recruitment-case && \
    mkdir build && \
    cd build && \
    cmake ../. && \
    make
```
The executable should now be in `twoday-recruitment-case/bin`

### Windows
Follow your standard procedure for building CMake projects. For example by using CMake Tools for VSCode or by pointing CMake GUI to the repo folder, generating, and opening the resulting solution files in visual studio. 