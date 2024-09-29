# ProgProj
image manipulation library in C++

# Membros
- Duarte 
- Guilherme
- João

# Objetivos:

## `prog::Color` | ~15%

* Construtores

  - [X] `Color()` | Default (cor corresponde ao preto)
  
  - [X] `Color(const Color& c)` | Por cópia
  
  - [X] `Color(rgb_value r, rgb_value g, rgb_value b)` | Por argumentos
* *Getters*

  - [X] `rgb_value red() const`
  
  - [X] `rgb_value green() const`
  
  - [X] `rgb_value blue() const`
* Referências mutáveis

  - [X] `rgb_value& red()`
  
  - [X] `rgb_value& green()`
  
  - [X] `rgb_value& blue()`

## `prog::Image` | ~15%

* Construtor e destruidor

  - [X] `Image(int w, int h, const Color& fill = {255, 255, 255})`
  
  - [X] `~Image()`
* *Getters*

  - [X] `int width() const` | Largura [0 .. width() - 1]
  
  - [X] `int height() const` | Altura [0 .. height() - 1]
* Referências

  - [X] `Color& at(int x, int y)` | Mutável
  
  - [X] `const Color& at(int x, int y) const` | *Read-only*

## `prog::Script` | 55%

* Construtor, destruidor e executável

  - [X] `Script(const std::string& filename)`
  
  - [X] `~Script`
  
  - [ ] `run()`

* Grupo I | Inicialização de imagens e I/O

  - [X] `blank w h r g b` | Nova imagem: dimensão (2) e cores (3)
  
  - [X] `open filename`
  
  - [X] `save filename`

* Grupo II | Manipulação de imagens (25%)

  - [X] `invert` | r -> 255 - r, ...
  
  - [X] `to_gray_scale` | Média das cores v -> (v, v, v)
  
  - [X] `replace r1 g1 b1 r2 g2 b2`
  
  - [X] `fill x y w h r g b` | Substitui a cor num retângulo de pixeís
  
  - [X] `h_mirror` | Espelho na horizontal: x -> width() - 1 - x
  
  - [X] `v_mirror` | Espelho na vertical: y -> height() - 1 - y
  
  - [X] `add filename x y r g b` | Copia os píxeis de um ficheiro para um retângulo da imagem atual, exceto os da cor rgb

* Grupo III | Mudança de dimensões (15%)

  - [X] `crop x y w h` | Cortar a imagem de acordo com um retângulo
  
  - [X] `rotate_left` | -90º
  
  - [X] `rotate_right` | +90º

## **Desafios adicionais:** (15%)

- [X] `median_filter ws` | Aplica o [filtro](https://en.wikipedia.org/wiki/Median_filter) num retângulo da imagem
> Opcional: Otimizar função

- [ ] `xpm2_open filename` | Chama a função em XPM2.hpp

  - [ ] `Image* loadFromXPM2(const std::string& file)`

- [ ] `xpm2_save filename` | Chama a função em XPM2.hpp

  - [ ] `void saveToXPM2(const std::string& file, const Image* image)`

## Código bem estruturado e comentado (15%)
> Opcional: Exceptions.cpp para cuidar de erros e de maus parâmetros

# Ferramentas de teste:

* ./runscript [dir]

  > "Process one or more image processing scripts"
* ./test Color / basic / [command] / xpm2_open / xpm2_save

  > "Execute one or more automated tests"
  > * Color | Testes em relação à class color
  > * basic | Testes simples de I/O de imagens
  > * [command] | Testa todos os scripts relacionados a um determinado comando
  > * xpm2_open/save | Testa o desafio adicional de XPM2
