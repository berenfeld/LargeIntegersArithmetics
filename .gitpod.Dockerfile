FROM gitpod/workspace-full

RUN sudo apt-get install -y  --no-install-recommends libgtest-dev gcovr
RUN git config --global alias.hist "log --pretty=format:'%h %ad | %s%d [%an]' --graph --date=short"
RUN git config --global alias.lol "log --graph --decorate --pretty=oneline --abbrev-commit --all"
RUN git config --global alias.mylog "log --pretty=format:'%h %s [%an]' --graph"
RUN git config --global alias.can "commit -a --amend --no-edit"
RUN git config --global core.editor "vim"

