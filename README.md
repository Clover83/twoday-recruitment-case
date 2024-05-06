# twoday-recruitment-case
## Assumptions
The main assumption I've made is that the point of the exercise was writing the logic, test cases, and dealing with flexible requirements. Not setting up a database, UI, or CLI. As such, the tests can be seen as examples of how to use the system.

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

[![](https://mermaid.ink/img/pako:eNrFVd9v2jAQ_lcsP9ENECHACpMqbYVukbq1gq6Tpry4zhWsJnZkO1VpRf722XFCE9J2016WByt3_u7uux-2nzAVEeAZDjmNiVJzRtaSJCEPdSGj4JLIO8bXc6LJZynuQOaMa5C3hEKOniww1O_dzhJUFusuWqVCWzw6YzyyQiclUjMSVxtHpdm9YBG64NckZtGCa7ntvIl4YLoJ2BkMDzkyn2O7eCBJGsMzWcsQlV_vG0nzgNcI5ohQze7ByurjAXKlpcm7i4xFjmJGgVO4EsG8hTPGwbzhVNKN8Roduv0fZTJhHYGdrVTV1cKL47HvIVOFeSktYc2UlkQzwRdSConArlfbFFzl695MxDedpW6GToXS_-C-XrUceJbs5-6aUMJLlxeUZimDMmQw_y70mch4JfN7y-fctfEyJhrcRl3TNDkVWRwZ1UoLWUxUU_2JUjDnpdQ3CC8JX8PpBujdy6T3hSlZBfPnGfnBFegrlsBKm1F-1pdQo5XFdsPBgkeVrkmkVeWqPxep1ZE4bxQX3VRSKjgcQg_TUjmSB6oWg_L2-CoyBfvgGysF_FY4ueeilpv10byUwhbZzTzYtT70tbGrgHb0wSx12FxkNzGgL6Dt_HUUUMEjZYlBdFQ7y4fpoUD9ZHrD-DlLmFYd1bx5iiQb6fV6Jy9cly5CAyh6vb8DWo-1eryG2NfBAdqXoEXVG-1wbQqo3z9pm78SdtnqfRG81r4CdTiCFcd9795Atef3nSldiAf9vhfiF1L6g0GbMu7iBGRCWGTewOKtCLHegDlLeGZ-I5N0aN7GncGRTIvVllM8uyWxgi7O0shcGuWLudemhP8SwshaZk7Esyf8gGfecNKfeKPJwPP88XDsT7t4i2cjvz_ypv5oOBh5A288GY53XfxYOBj0p_5w-sGf-lNvMBqPjo93vwFAs78y?type=png)](https://mermaid.live/edit#pako:eNrFVd9v2jAQ_lcsP9ENECHACpMqbYVukbq1gq6Tpry4zhWsJnZkO1VpRf722XFCE9J2016WByt3_u7uux-2nzAVEeAZDjmNiVJzRtaSJCEPdSGj4JLIO8bXc6LJZynuQOaMa5C3hEKOniww1O_dzhJUFusuWqVCWzw6YzyyQiclUjMSVxtHpdm9YBG64NckZtGCa7ntvIl4YLoJ2BkMDzkyn2O7eCBJGsMzWcsQlV_vG0nzgNcI5ohQze7ByurjAXKlpcm7i4xFjmJGgVO4EsG8hTPGwbzhVNKN8Roduv0fZTJhHYGdrVTV1cKL47HvIVOFeSktYc2UlkQzwRdSConArlfbFFzl695MxDedpW6GToXS_-C-XrUceJbs5-6aUMJLlxeUZimDMmQw_y70mch4JfN7y-fctfEyJhrcRl3TNDkVWRwZ1UoLWUxUU_2JUjDnpdQ3CC8JX8PpBujdy6T3hSlZBfPnGfnBFegrlsBKm1F-1pdQo5XFdsPBgkeVrkmkVeWqPxep1ZE4bxQX3VRSKjgcQg_TUjmSB6oWg_L2-CoyBfvgGysF_FY4ueeilpv10byUwhbZzTzYtT70tbGrgHb0wSx12FxkNzGgL6Dt_HUUUMEjZYlBdFQ7y4fpoUD9ZHrD-DlLmFYd1bx5iiQb6fV6Jy9cly5CAyh6vb8DWo-1eryG2NfBAdqXoEXVG-1wbQqo3z9pm78SdtnqfRG81r4CdTiCFcd9795Atef3nSldiAf9vhfiF1L6g0GbMu7iBGRCWGTewOKtCLHegDlLeGZ-I5N0aN7GncGRTIvVllM8uyWxgi7O0shcGuWLudemhP8SwshaZk7Esyf8gGfecNKfeKPJwPP88XDsT7t4i2cjvz_ypv5oOBh5A288GY53XfxYOBj0p_5w-sGf-lNvMBqPjo93vwFAs78y)

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
