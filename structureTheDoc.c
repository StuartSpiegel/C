
struct document get_document(char* text) {
    struct document doc;
    doc.data = NULL;
    doc.paragraph_count = 0;

    char *parag_token;
    char *rest_doc = text;
    // Fill paragraphs of document
    while ((parag_token = __strtok_r(rest_doc, "\n", &rest_doc))){
        if (doc.data == NULL){
            doc.data = malloc(sizeof(struct paragraph));
        } else {
            struct paragraph *parag_realloc;
            parag_realloc = realloc(doc.data, (doc.paragraph_count+1)*sizeof(struct paragraph));
            if (parag_realloc != NULL){
                doc.data = parag_realloc;
            }
        }
        struct paragraph parag;
        parag.data = NULL;
        parag.sentence_count = 0;

        char *sentence_token;
        char *rest_parag = parag_token;
        // Fill sentences of paragraph
        while ((sentence_token = __strtok_r(rest_parag, ".", &rest_parag))){
            if (parag.data == NULL){
                parag.data = malloc(sizeof(struct sentence));
            } else {
                struct sentence *sent_realloc;
                sent_realloc = realloc(parag.data, (parag.sentence_count+1)*sizeof(struct sentence));
                if (sent_realloc != NULL){
                    parag.data = sent_realloc;
                }
            }
            struct sentence sent;
            sent.data = NULL;
            sent.word_count = 0;

            char *word_token;
            char *rest_sentence = sentence_token;
            // Fill words of sentence
            while ((word_token = __strtok_r(rest_sentence, " ", &rest_sentence))){
                if (sent.data == NULL){
                    sent.data = malloc(sizeof(struct word));
                } else {
                    struct word *w_realloc;
                    w_realloc = realloc(sent.data, (sent.word_count+1)*sizeof(struct word));
                    if (w_realloc != NULL){
                        sent.data = w_realloc;
                    }
                }
                struct word w;
                w.data = malloc(strlen(word_token)*sizeof(char));
                strcpy(w.data, word_token);
                sent.data[sent.word_count] = w;
                sent.word_count++;
            }
            parag.data[parag.sentence_count] = sent;
            parag.sentence_count++;
        }
        doc.data[doc.paragraph_count] = parag;
        doc.paragraph_count++;
    }
    return doc;
}
