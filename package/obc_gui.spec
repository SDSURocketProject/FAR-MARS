Name: obc_gui
Version: 3.0.1
Release: 1
Summary: OBC-GUI Live Data Visualization Software
Requires: qt5-qtbase > 5.12
Requires: qt5-qtcharts > 5.12
License: MIT

%description
Graphical utility designed to interface with the SDSURP Lady Elizabeth
Rocket Onboard Computer to read, plot, and log data

%prep
mkdir -p $RPM_BUILD_ROOT/usr/local/bin
cp /builds/avionics/lady-liz-obc-gui/obc_gui $RPM_BUILD_ROOT/usr/local/bin
exit

%files
%attr(0755,root,root) /usr/local/bin/*

%clean
rm -rf $RPM_BUILD_ROOT/usr/local/bin
