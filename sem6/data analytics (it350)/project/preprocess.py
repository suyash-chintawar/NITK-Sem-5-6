import re
import pandas as pd

def decontracted(phrase):

    phrase = re.sub(r"won't", "will not", phrase)
    phrase = re.sub(r"can't", "can not", phrase)
    phrase = re.sub(r"gonna", "going to", phrase)
    phrase = re.sub(r"wanna", "want to", phrase)

    phrase = re.sub(r"n\'t", " not", phrase)
    phrase = re.sub(r"\'re", " are", phrase)
    phrase = re.sub(r"\'s", " is", phrase)
    phrase = re.sub(r"\'d", " would", phrase)
    phrase = re.sub(r"\'ll", " will", phrase)
    phrase = re.sub(r"\'t", " not", phrase)
    phrase = re.sub(r"\'ve", " have", phrase)
    phrase = re.sub(r"\'m", " am", phrase)
    phrase = re.sub(r"\.+", " ", phrase)
    phrase = re.sub(r"[^A-Za-z$]", " ", phrase)
    phrase = re.sub(r" +", " ", phrase)
    
    return phrase

def get_df(pref, testing=False):   

    dataset = []
    with open(pref + '_' + 'examples.txt') as examples:
        for example in examples:
            example = example[:-1].lower().split('\t')
            if example[0] != decontracted(example[0]):
                text = re.sub(example[0], "\$", example[2])
                text = decontracted(text)
                text = re.sub(r"\$", example[0], text)
                example[2] = text
            else:
                example[2] = decontracted(example[2])
            dataset.append(example)

    with open(pref + '_' + 'hypernyms.txt') as hypernyms:
        for index, line in enumerate(hypernyms):
            line = line[:-1].lower().split('\t')
            line = ';'.join(line)
            dataset[index].append(line)
            
    with open(pref + '_' + 'definitions.txt') as definitions:
        for index, line in enumerate(definitions):
            line = line[:-1].lower().split(';')
            for i in range(len(line)):
                line[i] = line[i].strip()
                if dataset[index][0] != decontracted(dataset[index][0]):
                    text = re.sub(dataset[index][0], "\$", line[i])
                    text = decontracted(text)
                    text = re.sub(r"\$", dataset[index][0], text)
                    line[i] = text
                else:
                    line[i] = decontracted(line[i])
            line = ';'.join(line)
            dataset[index].append(line)

    cols = ['target', 'position', 'sentence', 'hypernym', 'definition']

    if not testing:
        cols.append('label')
        with open(pref + '_' + 'labels.txt') as labels:
            for index, line in enumerate(labels):        
                line = line[:-1]
                dataset[index].append(line)
    
    df = pd.DataFrame(dataset, columns=cols)

    return df

dev_df = get_df('data/Development/dev')
train_df = get_df('data/Training/train')
test_df = get_df('data/Test/test', True)

dev_df.to_csv('dev.csv', index=None)
train_df.to_csv('train.csv', index=None)
test_df.to_csv('test.csv', index=None)