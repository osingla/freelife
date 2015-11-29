Summary: Game of Conway's Life
Name: freelife
Version: 0
Release: 2
%define src %{name}
License: BSD
Group: Amusements/Games
URL:		http://freelife.sourceforge.net/
Prefix: %{_prefix}
Buildroot: %{_tmppath}/%{name}

%description
This program allows the user to play the game of Life (Conway's game of life).

%prep
#

%build
#

%install
#

%files
%attr(755,root,root) %{_bindir}/*

%clean
rm -rf $RPM_BUILD_ROOT

%changelog
* Tue Apr 1 2003 Olivier Singla <olivier@singla.us>
- Created the RPM.

