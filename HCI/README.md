# HCI

## Statistics

### p

At its core, a p-value is a statistical measure that helps us determine the strength of evidence against a null hypothesis. The null hypothesis is the default assumption, usually stating that there's no effect or no difference.

For example, if we're running an A/B test on a new website feature, the null hypothesis would be that the new feature has no impact on user conversion rates.

The p-value is the probability of observing our data, or something even more extreme, if the null hypothesis were true. A small p-value (typically below 0.05) suggests that our observed data is unlikely to have occurred by random chance alone, providing evidence to reject the null hypothesis in favor of the alternative—that there is an effect.

However, and this is crucial, the p-value is not the probability that the null hypothesis is true, nor is it the probability that our finding is a fluke. This is one of the most common and dangerous misinterpretations of p-values. A p-value of 0.04 doesn't mean there's a 4% chance the null hypothesis is correct.It simply indicates the degree of incompatibility between our data and the null hypothesis.

Furthermore, statistical significance does not automatically equal practical or business significance. With a large enough sample size, you can find a statistically significant p-value for a tiny, meaningless effect. For instance, we could find a statistically significant increase in conversion rate of 0.001%, which, while real, might not be worth the engineering cost to implement.

This is why, at a senior level, we never look at the p-value in a vacuum.

In my work, I use the p-value as one piece of a larger puzzle to inform decisions. Here's how I approach it:

* **Complement with Effect Size and Confidence Intervals:** I always pair the p-value with the effect size. The p-value tells me if there's likely an effect, while the effect size tells me *how big* that effect is. A confidence interval then gives us a range of plausible values for that effect size, which helps quantify the uncertainty around our estimate.

* **Consider the Business Context:** A key part of my role is to ask, 'So what?' Does this statistically significant result translate into a meaningful impact on our business goals? Is the return on investment positive? This requires collaborating with stakeholders to understand the practical implications of the findings.

* **Power and Sample Size:** Before even running an experiment, I consider the statistical power. That is, what is the probability that our test will detect an effect of a certain size, if there is one? Under-powered studies can lead to non-significant p-values even when a real, meaningful effect exists.

* **Alternatives and Bayesian Methods:** I'm also cognizant of the limitations of the frequentist approach. In some cases, Bayesian methods can be more intuitive. Instead of a p-value, a Bayesian approach can help us talk about the probability of a hypothesis being true, given the data, which can be more directly actionable for stakeholders.

In essence, I treat the p-value as a smoke detector. It can alert you to a potential fire, but it doesn't tell you how big the fire is, where it is, or what you should do about it. That requires further investigation and a holistic view of the evidence."

## Bayesian Approach

The Bayesian approach is a powerful framework for statistical inference that fundamentally redefines our understanding of probability. Unlike the more traditional frequentist approach, which views probability as the long-run frequency of an event, the Bayesian perspective treats probability as a measure of belief or confidence in a proposition. This allows us to update our beliefs as we gather more evidence, making it an intuitive and dynamic way to reason about uncertainty.

At the heart of the Bayesian approach is **Bayes' Theorem**, a mathematical formula that provides a systematic way to update our beliefs in light of new data. It connects the probability of a hypothesis before seeing the data to the probability of the hypothesis after seeing the data.

### The Core Components of the Bayesian Approach

The Bayesian framework consists of three key ingredients:

* **Prior Probability (Prior):** This represents our initial belief about a parameter or hypothesis before we've seen any data. This "prior" can be based on previous research, expert opinion, or a general lack of knowledge (an "uninformative prior"). It's a way to formally incorporate existing knowledge into our analysis.

* **Likelihood:** This is the probability of observing the collected data, given a particular value of the parameter we're interested in. It quantifies how well our hypothesis explains the data we've gathered.

* **Posterior Probability (Posterior):** This is the updated belief about the parameter or hypothesis after taking the evidence (our data) into account. The posterior is calculated by combining the prior and the likelihood using Bayes' Theorem. In essence, the posterior is a weighted average of our prior beliefs and the information from our data.

**The process is iterative:** today's posterior belief can become tomorrow's prior belief as new data becomes available. This allows for a continuous and rational updating of our knowledge.

### A Simple Analogy: Is it Going to Rain?

Imagine you wake up in the morning and want to decide if you should take an umbrella.

* **Prior:** You live in a desert, so your *prior belief* is that there is a low probability of rain, say 10%.
* **Evidence (Data):** You look outside and see dark, heavy clouds.
* **Likelihood:** The *likelihood* of seeing dark clouds if it is going to rain is high.
* **Posterior:** Combining your prior belief (it rarely rains) with the new evidence (dark clouds), you update your belief. Your *posterior probability* of rain is now much higher than your initial 10%, and you decide to take an umbrella.

### How is this Different from the Frequentist Approach?

The key philosophical difference lies in the treatment of parameters (the unknown quantities we want to estimate).

* **Frequentist View:** A parameter is a fixed, unknown constant. We can't assign a probability to it. Instead, we talk about the probability of our data given the parameter. This leads to concepts like p-values and confidence intervals, which can be less intuitive to interpret.

* **Bayesian View:** A parameter is a random variable, meaning we can describe our uncertainty about it with a probability distribution. This allows us to make direct probabilistic statements about the parameter itself, such as "there is a 95% probability that the true value of the parameter lies within this range" (a credible interval).

### Why Use the Bayesian Approach?

The Bayesian framework offers several advantages:

* **Intuitive Interpretation:** The results, such as credible intervals, are often more straightforward to understand than their frequentist counterparts. You can directly talk about the probability of a hypothesis being true.
* **Incorporation of Prior Knowledge:** It provides a formal mechanism to include existing information, which can be particularly useful when dealing with limited data.
* **Flexibility:** It is well-suited for a wide range of problems, from simple A/B testing to complex machine learning models.
* **Good with Small Datasets:** Bayesian methods can provide valuable insights even with small sample sizes, whereas frequentist methods often require larger samples for reliable results.

However, it's also important to acknowledge potential challenges. The choice of a prior can be subjective and can influence the results, which can sometimes be a point of contention. Bayesian methods can also be more computationally intensive, especially for complex models.
