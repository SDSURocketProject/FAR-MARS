# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public int `[`main`](#main_8cpp_1a0ddf1224851353fc92bfbff6f499fa97)`(int argc,char * argv)`            | Control Software Main
`class `[`about`](#classabout) | 
`class `[`logger`](#classlogger) | 
`class `[`mainwindow`](#classmainwindow) | 
`class `[`news`](#classnews) | 
`class `[`warning`](#classwarning) | 

## Members

#### `public int `[`main`](#main_8cpp_1a0ddf1224851353fc92bfbff6f499fa97)`(int argc,char * argv)` {#main_8cpp_1a0ddf1224851353fc92bfbff6f499fa97}

Control Software Main

Zack Mudd [zmudd@sdsu.edu](mailto:zmudd@sdsu.edu)

# class `about` {#classabout}

```
class about
  : public QMainWindow
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`about`](#classabout_1a860b15d9fedd569d066998ca10596fc0)`(QWidget * parent)` | About Page
`public  `[`~about`](#classabout_1a0d7ebadcc35f58044fe6cbc7d8d4f636)`()` | About Class Destructor

## Members

#### `public  explicit `[`about`](#classabout_1a860b15d9fedd569d066998ca10596fc0)`(QWidget * parent)` {#classabout_1a860b15d9fedd569d066998ca10596fc0}

About Page

Zack Mudd [zmudd@sdsu.edu](mailto:zmudd@sdsu.edu) About Class Constructor

#### `public  `[`~about`](#classabout_1a0d7ebadcc35f58044fe6cbc7d8d4f636)`()` {#classabout_1a0d7ebadcc35f58044fe6cbc7d8d4f636}

About Class Destructor

# class `logger` {#classlogger}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`logger`](#classlogger_1a4f753a510e00c892b38e95c2284363a6)`()` | Data Logger Class
`public void `[`setFile`](#classlogger_1a3bb56560823628407584e163d8d70a60)`(char * newfilename)` | Set path to log file
`public void `[`openFile`](#classlogger_1a6f1953b7fa70aa4e561d2a8aa3aa67af)`()` | Open log for writing
`public void `[`closeFile`](#classlogger_1a6b1421875c6d245f533f3197b15d9856)`()` | Close file after writing
`public int `[`isOpen`](#classlogger_1aabde36bc4c79b209c5c9b17a256c5858)`()` | Check if log is currently opened
`public void `[`appendData`](#classlogger_1a6a88a186a97af2aec42abd1ff03fe821)`(const char * data)` | Append data to file, generic
`public void `[`appendData`](#classlogger_1ae8678e52b408e2a62986167d8aee8691)`(const char * data,int newLine)` | Append data to file, EOL-defined
`public void `[`newLine`](#classlogger_1a3efa363e127b361b0d94f907e27ab6e6)`()` | Append newline to file

## Members

#### `public  `[`logger`](#classlogger_1a4f753a510e00c892b38e95c2284363a6)`()` {#classlogger_1a4f753a510e00c892b38e95c2284363a6}

Data Logger Class

Zack Mudd [zmudd@sdsu.edu](mailto:zmudd@sdsu.edu) Logger Class Constructor

#### `public void `[`setFile`](#classlogger_1a3bb56560823628407584e163d8d70a60)`(char * newfilename)` {#classlogger_1a3bb56560823628407584e163d8d70a60}

Set path to log file

v0.2.0 

#### Parameters
* `char*` path to be used as filename

#### `public void `[`openFile`](#classlogger_1a6f1953b7fa70aa4e561d2a8aa3aa67af)`()` {#classlogger_1a6f1953b7fa70aa4e561d2a8aa3aa67af}

Open log for writing

#### `public void `[`closeFile`](#classlogger_1a6b1421875c6d245f533f3197b15d9856)`()` {#classlogger_1a6b1421875c6d245f533f3197b15d9856}

Close file after writing

#### `public int `[`isOpen`](#classlogger_1aabde36bc4c79b209c5c9b17a256c5858)`()` {#classlogger_1aabde36bc4c79b209c5c9b17a256c5858}

Check if log is currently opened

#### Returns
int 1 if open, else 0

#### `public void `[`appendData`](#classlogger_1a6a88a186a97af2aec42abd1ff03fe821)`(const char * data)` {#classlogger_1a6a88a186a97af2aec42abd1ff03fe821}

Append data to file, generic

#### Parameters
* `const` char* text to be appended to file 

#### Returns
spawns warning popup if file not opened for writing

#### `public void `[`appendData`](#classlogger_1ae8678e52b408e2a62986167d8aee8691)`(const char * data,int newLine)` {#classlogger_1ae8678e52b408e2a62986167d8aee8691}

Append data to file, EOL-defined

#### Parameters
* `const` char* text to be appended to file 

* `int` append newline to end of data, 1 for yes 0 for no 

#### Returns
spawns warning popup if file not opened for writing

#### `public void `[`newLine`](#classlogger_1a3efa363e127b361b0d94f907e27ab6e6)`()` {#classlogger_1a3efa363e127b361b0d94f907e27ab6e6}

Append newline to file

#### Returns
spawns warning window if file not opened for writing

# class `mainwindow` {#classmainwindow}

```
class mainwindow
  : public QMainWindow
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`mainwindow`](#classmainwindow_1a0fdd6899038444a0c46052859468f67f)`(QWidget * parent)` | Control Software Main Window
`public  `[`~mainwindow`](#classmainwindow_1a5443e012964c892ef6015e7cebf62a67)`()` | Mainwindow destructor

## Members

#### `public  explicit `[`mainwindow`](#classmainwindow_1a0fdd6899038444a0c46052859468f67f)`(QWidget * parent)` {#classmainwindow_1a0fdd6899038444a0c46052859468f67f}

Control Software Main Window

Zack Mudd [zmudd@sdsu.edu](mailto:zmudd@sdsu.edu) Mainwindow Constructor

#### Parameters
* `QWidget*` parent QWidget

#### `public  `[`~mainwindow`](#classmainwindow_1a5443e012964c892ef6015e7cebf62a67)`()` {#classmainwindow_1a5443e012964c892ef6015e7cebf62a67}

Mainwindow destructor

# class `news` {#classnews}

```
class news
  : public QMainWindow
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`news`](#classnews_1a8f333292753e37dc3bc02de8648c4167)`(QWidget * parent)` | Whats New Window
`public  `[`~news`](#classnews_1aa35b02909541ad5f6a1eb015e8c991ca)`()` | News destructor

## Members

#### `public  explicit `[`news`](#classnews_1a8f333292753e37dc3bc02de8648c4167)`(QWidget * parent)` {#classnews_1a8f333292753e37dc3bc02de8648c4167}

Whats New Window

Zack Mudd [zmudd@sdsu.edu](mailto:zmudd@sdsu.edu) News constructor

#### Parameters
* `QWidget*` Parent object

#### `public  `[`~news`](#classnews_1aa35b02909541ad5f6a1eb015e8c991ca)`()` {#classnews_1aa35b02909541ad5f6a1eb015e8c991ca}

News destructor

# class `warning` {#classwarning}

```
class warning
  : public QMainWindow
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`warning`](#classwarning_1acc394132d1798706fb687361c51ec14a)`(QWidget * parent)` | Generic Warning Popup Class
`public  `[`~warning`](#classwarning_1a308909647ea89450f2b5b0d56a91bd39)`()` | 
`public void `[`setWarning`](#classwarning_1a81dadd00d0568986c68b9a21793441ab)`(QString)` | Set text of warning popup

## Members

#### `public  explicit `[`warning`](#classwarning_1acc394132d1798706fb687361c51ec14a)`(QWidget * parent)` {#classwarning_1acc394132d1798706fb687361c51ec14a}

Generic Warning Popup Class

Zack Mudd [zmudd@sdsu.edu](mailto:zmudd@sdsu.edu)

#### `public  `[`~warning`](#classwarning_1a308909647ea89450f2b5b0d56a91bd39)`()` {#classwarning_1a308909647ea89450f2b5b0d56a91bd39}

#### `public void `[`setWarning`](#classwarning_1a81dadd00d0568986c68b9a21793441ab)`(QString)` {#classwarning_1a81dadd00d0568986c68b9a21793441ab}

Set text of warning popup

#### Parameters
* `QString` text to display

Generated by [Moxygen](https://sourcey.com/moxygen)