/*
 * Tagger.h
 *
 *  Created on: Mar 16, 2015
 *      Author: mszhang
 */

#ifndef SRC_NNSEmbSemiO1CRFTagger_H_
#define SRC_NNSEmbSemiO1CRFTagger_H_


#include "N3L.h"
#include "NNSEmbSemiO1CRF.h"
#include "Options.h"
#include "Instance.h"
#include "Example.h"


#include "Pipe.h"
#include "Utf.h"

using namespace nr;
using namespace std;

class Tagger {


public:
	Alphabet m_labelAlphabet;
	Alphabet m_clabelAlphabet;
	Alphabet m_seglabelAlphabet;
	Alphabet m_cseglabelAlphabet;
	hash_map<int, int> m_label_f2c;
	hash_map<int, int> m_seg_f2c;
	vector<int> maxLabelLength;
	vector<int> maxcLabelLength;
	hash_set<string> ignoreLabels;
	hash_map<string, int> m_feat_stats;
	hash_map<string, int> m_word_stats;
	hash_map<string, int> m_char_stats;
	vector<hash_map<string, int> > m_type_stats;
	hash_map<string, int> m_seg_stats; // read it by file

public:
	Options m_options;

	Pipe m_pipe;

	NNSEmbSemiO1CRF m_classifier;


public:
	Tagger();
	virtual ~Tagger();

public:

	int createAlphabet(const vector<Instance>& vecTrainInsts);
	int addTestAlpha(const vector<Instance>& vecInsts);
	void collectSEGAlpha(const vector<Example>& vecInsts, const string& segFile); //notice: seg embeddings are fixed during training


	void extractLinearFeatures(vector<string>& features, const Instance* pInstance, int idx);
	void extractFeature(Feature& feat, const Instance* pInstance, int idx);

	void convert2Example(const Instance* pInstance, Example& exam, bool bTrain = false);
	void initialExamples(const vector<Instance>& vecInsts, vector<Example>& vecExams, bool bTrain = false);

public:
	void train(const string& trainFile, const string& devFile, const string& testFile, const string& modelFile, const string& optionFile);
	int predict(const vector<Feature>& features, vector<string>& outputs);
	void test(const string& testFile, const string& outputFile, const string& modelFile);

	void writeModelFile(const string& outputModelFile);
	void loadModelFile(const string& inputModelFile);

};

#endif /* SRC_NNSEmbSemiO1CRFTagger_H_ */
