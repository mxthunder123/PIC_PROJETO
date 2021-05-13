// JOGO DA MEMÓRIA - GENIOS
// MEMBROS: Arthur Oliveira Purcino, klarine Mendonça Silva, Pedro Henrique Sena Lima
// Link do Thinkercad: https://www.tinkercad.com/things/8TiDhaiXTgY-stunning-borwo/editel?sharecode=ec7bfpsGE1sXplnLPmfAaP4-AOo3FD9d2W1bEdCW9Pw



//Definindo as notas para os sons

#define NOTE_D4  294

#define NOTE_G4  392

#define NOTE_A4  440

#define NOTE_A5  880

 
//Criando o array para os 4 sons para sortear um som

int sounds[4] = { NOTE_A5, NOTE_A4, NOTE_G4, NOTE_D4 };

// A sequência de até 100 itens vai começar vazia.

int sequence[100] = {};

// Indica a rodada atual que o jogo se encontra.

int current_round = 0;

// Indica o passo atual dentro da sequência, é usado enquanto a sequência está sendo reproduzida.
 
int current_step = 0;

//Indica o numero de rodadas que o jogador conseguiu completar

 int pontuation = 0;

/*

 * Indica o pino de áudio, leds e botões.

 * Os pinos de leds e botões estão em ordem, relacionados uns aos outros, ou

 * seja, o primeiro led está relacionado ao primeiro botão. A ordem destas

 * sequências também estão relacionadas a ordem dos tons.

 */

int pinSong = 7;

int pinLeds[4] = { 11, 10, 9, 8 };

int pinButtons[4] = { 6, 5, 4, 3 };

 

// Indica se um botão foi pressionado durante o loop principal.

int button_pressed = 0;

// Flag indicando se o jogo acabou.

int game_over = false;

 

void setup() {

  // Definindo o modo dos pinos dos Leds como saída.

  for (int i = 0; i <= 3; i++) {

    pinMode(pinLeds[i], OUTPUT);

  }
 

  // Definindo o modo dos pinos dos Botões como entrada.
  for (int i = 0; i <= 3; i++) {
    pinMode(pinButtons[i], INPUT_PULLUP);
  }

 
  // Definindo o modo do pino de Áudio como saída.

  pinMode(pinSong, OUTPUT);

 

  // Inicializando o random através de uma leitura da porta analógica.
  // Esta leitura gera um valor variável entre 0 e 1023.

  randomSeed(analogRead(0));
  
  Serial.begin(9600);

}
 
void loop() {

  
  // Se perdeu o jogo  todas as variáveis são reinicializadas e
   // a pontuacao daquela partida é escrita no serial.

  if (game_over) {
    Serial.print("Sua pontuacao: ");
    Serial.print(pontuation-1);
    Serial.print("\n");
    pontuation = 0;
    

    int sequence[100] = {};

    current_round = 0;
    current_step = 0;
    

    game_over = false;

  }
 
  // Toca um som de início para anúnicar que o jogo está começando quando é a primeira rodada.
  if (current_round == 0 ) {

    
	playStartSound();

    delay(500);

  }
 
	
  // Chama a função que inicializa a próxima rodada.

  nextRound();

  // Reproduz a sequência atual.

  playSequence();

  // Aguarda os botões serem pressionados pelo jogador.

  waitPlayer();
 

  // Aguarda 1 segundo entre cada jogada.

  delay(1000);
}
 

// Sorteia um novo item e adiciona na sequência.

void nextRound() {

  int number_drawn = random(0, 4);

  sequence[current_round++] = number_drawn;
  
  Pontuation();

}

 

// Reproduz a sequência para ser memorizada.

void playSequence() {
  for (int i = 0; i < current_round; i++) {

    tone(pinSong, sounds[sequence[i]]);

    digitalWrite(pinLeds[sequence[i]], HIGH);
    delay(500);

    noTone(pinSong);

    digitalWrite(pinLeds[sequence[i]], LOW);
    delay(100);

  }
	
  noTone(pinSong);

}

 

// Aguarda o jogador iniciar sua jogada.

void waitPlayer() {

  for (int i = 0; i < current_round; i++) {
    waitMove();

    checkMove();

 
    if (game_over) {

      break;
    }

 

    current_step++;

  }

 

  // Redefine a variável para 0.

  current_step = 0;
}

// aguarda o jogador apertar os botoes correspondentes
void waitMove() {

  boolean move_made = false;

  while (!move_made) {

    for (int i = 0; i <= 3; i++) {

      if (digitalRead(pinButtons[i]) == LOW) {

        // Dizendo qual foi o botao pressionado.

        button_pressed = i;

 

        tone(pinSong, sounds[i]);

        digitalWrite(pinLeds[i], HIGH);

        delay(300);

        digitalWrite(pinLeds[i], LOW);

        noTone(pinSong);

 

        move_made = true;
        
		
      }

    }

    delay(10);
  }
}

 //checa o movimento e determina se o jogo acabou
void checkMove() {
  if (sequence[current_step] != button_pressed) {
    // GAME OVER.
	
    for (int i = 0; i <= 3; i++) {
      tone(pinSong, sounds[i]);
      digitalWrite(pinLeds[i], HIGH);

      delay(200);

      digitalWrite(pinLeds[i], LOW);
      noTone(pinSong);
    }

 

    tone(pinSong, sounds[3]);

    for (int i = 0; i <= 3; i++) {

      digitalWrite(pinLeds[0], HIGH);

      digitalWrite(pinLeds[1], HIGH);

      digitalWrite(pinLeds[2], HIGH);

      digitalWrite(pinLeds[3], HIGH);

      delay(100);

      digitalWrite(pinLeds[0], LOW);

      digitalWrite(pinLeds[1], LOW);

      digitalWrite(pinLeds[2], LOW);

      digitalWrite(pinLeds[3], LOW);

      delay(100);

    }

    noTone(pinSong);

 

    game_over = true;

  }

}
 //Calculando a pontuacao
void Pontuation(){
  //A cada rodada correta soma-se mais 1 a pontuacao
  pontuation+=1;
  

}

//Funcao para tocar o som ao iniciar o jogo
void playStartSound() {

  tone(pinSong, sounds[0]);

  digitalWrite(pinLeds[0], HIGH);

  digitalWrite(pinLeds[1], HIGH);
  digitalWrite(pinLeds[2], HIGH);
  digitalWrite(pinLeds[3], HIGH);

  delay(500);

  digitalWrite(pinLeds[0], LOW);
  digitalWrite(pinLeds[1], LOW);
  digitalWrite(pinLeds[2], LOW);

  digitalWrite(pinLeds[3], LOW);
  delay(500);
  noTone(pinSong);
}
