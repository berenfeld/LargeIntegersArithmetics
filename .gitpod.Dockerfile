FROM gitpod/workspace-full

RUN sudo apt-get update
RUN sudo apt-get dist-upgrade -y
RUN sudo apt-get install -y --no-install-recommends libgtest-dev gcovr clang-format libbenchmark-dev python3-dev
RUN git config --global alias.hist "log --pretty=format:'%h %ad | %s%d [%an]' --graph --date=short"
RUN git config --global alias.lol "log --graph --decorate --pretty=oneline --abbrev-commit"
RUN git config --global alias.lola "log --graph --decorate --pretty=oneline --abbrev-commit --all"
RUN git config --global alias.mylog "log --pretty=format:'%h %s [%an]' --graph"
RUN git config --global alias.can "commit -a --amend --no-edit"
RUN git config --global alias.co "checkout --recurse-submodules"
RUN git config --global core.editor "vim"

RUN cd /tmp && git clone https://github.com/gabime/spdlog.git
RUN cd /tmp/spdlog && mkdir build && cd build && cmake ..
RUN cd /tmp/spdlog/build && make -j && sudo make install
