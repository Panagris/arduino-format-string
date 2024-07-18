#include <stdarg.h>

const int LED_PIN = 2;
const int TWENTY_MIN = 1.2e+6;
// /*
// ... to define variable character length
void format_print(const char *format_string, ...) {
  // copy to maintain old pointer for later loop
  const char* copy_form = format_string;
  // Coulnd't figure out multiline expression
  String MISMATCH_ERROR = "<-- ERROR: FORMAT_PRINT() ";
  MISMATCH_ERROR += "-- MORE TOKENS THAN ARGUMENTS -->";
  
  int count_special_chars = 0;
  unsigned int index;
  while(*copy_form){
    switch(*copy_form){
      case '%':
        count_special_chars++;
        break;
    }
    copy_form++;
  }
  // Serial.print("Count special: "); Serial.println(count_special_chars);
  String return_string = ""; int count_va_list_special_chars = 0;
  va_list args;
  // Begin a variable argument of this functions arguments (args)
  // starting after the argument format_string
  va_start(args, format_string);

  while (*format_string) {
    switch (*format_string) {
      case '%':
        count_va_list_special_chars++;
        if(count_va_list_special_chars > count_special_chars){
          Serial.println(MISMATCH_ERROR);
          return;
        }
        format_string++;
        switch (*format_string) {
          case 'd':
            return_string += va_arg(args, int);
            break;
          case 'f':
            return_string += va_arg(args, float);
            break;
          case 's':
            return_string += va_arg(args, char *);
            break;
          default: // If no special char provided, assume regular % sign.
            return_string += '%';
            break;
        }
        break;
      default:
        return_string += *format_string;
        break;
    }
    format_string++;
  }

  // Clear memory taken by va_start().
  va_end(args);
  Serial.println(return_string);
}
// */
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  format_print("Hi, my name is %s and I am %d years old! %f %d", "Chiagozie", 20, .5);
}


void loop() {

}
