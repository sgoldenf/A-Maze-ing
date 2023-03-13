#include "facade.h"

namespace s21 {
auto Facade::LoadMaze(const std::string& filepath) -> void {
  MazeFileReader r(filepath);
  maze_ = r.ReadFile();
}

auto Facade::GenerateMaze(Field::Size size) -> void {
  maze_ = std::make_unique<Maze>(size);
}

auto Facade::SaveMaze(const std::string& filepath) -> void {
  MazeFileWriter w(filepath);
  w.WriteToFile(*maze_);
}

auto Facade::SolveMaze(Coordinate begin, Coordinate end) -> Maze::Coordinates* {
  solution_ = maze_->Solve(begin, end);
  return &solution_;
}

auto Facade::LoadCave(const std::string& filepath) -> void {
  CaveFileReader r(filepath);
  cave_ = r.ReadFile();
  ReplaceMemento();
}

auto Facade::GenerateCave(Field::Size size, double chance) -> void {
  cave_ = std::make_unique<Cave>(size, chance);
  ReplaceMemento();
}

auto Facade::SaveCave(const std::string& filepath) -> void {
  CaveFileWriter w(filepath);
  w.WriteToFile(*cave_);
}

auto Facade::CaveIteration(int birth_limit, int death_limit) -> bool {
  return cave_->NextIteration(birth_limit, death_limit);
}

auto Facade::ResetCave() -> void {
  if (cave_memento_) {
    cave_->ReinstateCellsMemento(cave_memento_);
  }
}

auto Facade::ReplaceMemento() -> void {
  if (cave_memento_) {
    delete cave_memento_;
    cave_memento_ = nullptr;
  }
  cave_memento_ = cave_->CreateCellsMemento();
}
}  // namespace s21
