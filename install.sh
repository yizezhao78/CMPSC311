curl http://www.cse.psu.edu/~yuw17/cmpsc311/vagrant/.vimrc > ~/.vimrc
chmod 600 ~/.vimrc
if ! [ -d ~/.vim/after/ftplugin ]; then
  mkdir -p ~/.vim/after/ftplugin
fi
curl http://www.cse.psu.edu/~yuw17/cmpsc311/vagrant/c.vim > ~/.vim/after/ftplugin/c.vim
chmod 600 ~/.vim/after/ftplugin/c.vim
#echo "Enter your psuid of the form xxx1234"
#read PSUID
#curl http://www.cse.psu.edu/~yuw17/cmpsc311/vagrant/config | sed 's/xxx1234/'"$PSUID"'/' > ~/.ssh/config
#chmod 600 ~/.ssh/config
