# System Design

These are high-level architectural discussions, and a real-world implementation would involve numerous teams and detailed design documents for each component.

## Examples

### How would you design Instagram / Instagram Stories?

Designing a platform like Instagram requires a focus on high-availability for both media uploads and feed consumption. Instagram Stories adds the interesting challenge of ephemeral data.

**Core Functional Requirements:**

* Users can upload photos and videos.
* Users can view a feed of content from people they follow.
* Users can post temporary "Stories" that disappear after 24 hours.
* Users can follow other users and be followed.
* Users can like and comment on posts.

**Non-Functional Requirements:**

* **High Availability & Reliability:** The system must be highly available with minimal downtime.
* **Low Latency:** Feeds and stories should load quickly for a seamless user experience.
* **Scalability:** The system must handle a massive number of users and a huge volume of media uploads and views.

**High-Level Architecture:**

Our design would be a distributed, microservices-based architecture.

* **Clients (Mobile/Web):** These are the user-facing applications. They interact with our backend services via APIs.
* **API Gateway:** A single entry point for all client requests. It handles routing, authentication, and rate limiting.
* **Microservices:**
  * **User Service:** Manages user profiles, authentication, and the social graph (followers/following).
  * **Media Service:** Handles the uploading, processing, and storage of images and videos. When a user uploads media, this service would generate different sizes and formats for various devices and network conditions.
  * **Feed Service:** Generates the user's home feed. For scalability, we would pre-compute feeds for active users and store them in a cache like Redis. This avoids costly computations on every request.
  * **Story Service:** Manages the ephemeral stories. It would handle the 24-hour expiration logic.
  * **Social Graph Service:** Manages the follower/following relationships, which is crucial for feed and story distribution.

**Data Storage:**

* **Metadata:** For user data, post metadata (likes, comments, timestamps), and the social graph, a distributed SQL database like Spanner or a NoSQL database like Cassandra would be suitable due to its scalability and fault tolerance.
* **Media Storage:** Photos and videos would be stored in a distributed object storage system like Google Cloud Storage or AWS S3. A Content Delivery Network (CDN) would be used to cache media content closer to users for faster delivery.
* **Stories Storage:** Since stories are temporary, a NoSQL database with a Time-to-Live (TTL) feature would be ideal. When a story is posted, we set a TTL of 24 hours, and the database will automatically handle its deletion.

**Instagram Stories Specifics:**

The ephemeral nature of stories allows for some optimization. We can use a less durable but faster storage solution for the story pointers. The core logic involves a service that retrieves stories from users you follow, filtering out those older than 24 hours. A dedicated service would periodically clean up expired story data from the object store.

---

### How would you design a messaging app like WhatsApp or Telegram?

The key challenges in designing a messaging app are real-time message delivery, handling online/offline status, and ensuring message persistence and security.

**Core Functional Requirements:**

* One-on-one and group chat functionality.
* Real-time message sending and receiving.
* Show user's online/offline status.
* Message delivery status (sent, delivered, read).
* End-to-end encryption for privacy.

**Non-Functional Requirements:**

* **Low Latency:** Messages should be delivered almost instantly.
* **High Availability & Reliability:** The service must be always on and guarantee message delivery.
* **Scalability:** Support for billions of users and messages per day.

**High-Level Architecture:**

* **Clients (Mobile/Web):** The user's messaging application.
* **API Gateway:** Manages connections from clients. For real-time communication, this would involve managing persistent connections.
* **Real-time Communication:**
  * **WebSockets:** For a persistent, bidirectional connection between the client and the server. This is crucial for instantly pushing messages to the recipient.
* **Microservices:**
  * **User Service:** Handles user authentication and profiles.
  * **Chat Service:** The core of the system, responsible for message routing. When a user sends a message, it's routed to the appropriate recipient(s).
  * **Presence Service:** Manages the online/offline status of users. Clients would send heartbeats to this service to indicate they are online.
  * **Notification Service:** For users who are offline, this service would send push notifications.
* **Message Queue:** A system like Kafka or RabbitMQ would be used to decouple the message sending and processing. When a message is sent, it's published to a queue, and a worker process picks it up for delivery. This provides resilience against failures.

**Data Storage:**

* **Message Data:** A distributed, scalable NoSQL database like Bigtable or Cassandra is a good choice for storing chat history. Messages would be indexed by user and chat ID for efficient retrieval.
* **User Metadata:** A relational database or a key-value store can be used for user profiles.
* **Offline Message Storage:** For users who are offline, messages are stored temporarily until they come back online. A database or a persistent message queue can handle this.

---

### How would you design Facebook Messenger?

The design for Facebook Messenger shares many similarities with WhatsApp but is more tightly integrated with the broader Facebook ecosystem.

**Key Differences from a Standalone Messenger:**

* **Integration with Facebook's Social Graph:** Messenger leverages the existing friend connections from Facebook.
* **Unified Identity:** A single identity is used across Facebook and Messenger.
* **Richer Features:** Messenger often has more integrated features like games, bots, and payments.

**High-Level Design Principles:**

The core architecture would be very similar to the WhatsApp design, utilizing WebSockets for real-time communication and a microservices architecture.

* **Authentication:** Would be handled by Facebook's central authentication service.
* **Social Graph Integration:** The Chat Service would query Facebook's social graph to determine message permissions and recipient details.
* **Data Model:** The data model would include links back to Facebook's user profiles.

The key takeaway is that while the core messaging functionality is similar, the system design must account for deep integration with a larger platform.

---

### How would you design Facebook's live update of comments on posts?

This is a classic real-time system design problem. The goal is to push new comments to all users viewing a post without them needing to refresh the page.

**Core Functional Requirements:**

* Users see new comments on a post in real-time.
* The system should handle a large number of concurrent viewers for a single post.

**Non-Functional Requirements:**

* **Low Latency:** Updates should appear with minimal delay.
* **Scalability:** The system needs to support millions of concurrent connections.

**High-Level Architecture:**

* **Client-Side:** When a user views a post, the client establishes a persistent connection with a real-time update service.
* **Real-time Communication:**
  * **WebSockets or Server-Sent Events (SSE):** WebSockets provide a bidirectional channel, while SSE is a simpler, unidirectional protocol from server to client. For just pushing comments, SSE can be a very efficient choice.
* **Backend Flow:**
    1. A user submits a new comment via a standard HTTP POST request to the Comments Service.
    2. The Comments Service persists the comment to the database.
    3. After successful storage, the Comments Service publishes an event to a message queue (like Kafka or a Pub/Sub system). The event contains the new comment and the ID of the post it belongs to.
    4. A **Real-time Service** (or a "Fanout Service") is subscribed to this message queue.
    5. The Real-time Service receives the new comment event. It then looks up all the active client connections subscribed to that specific post.
    6. It pushes the new comment data down the persistent connections (WebSockets or SSE) to all connected clients.

**Key Components:**

* **Connection Manager:** A service responsible for managing the large number of persistent connections from clients.
* **Pub/Sub System:** To broadcast new comment events to the Real-time Service. This decouples the comment submission logic from the real-time push mechanism.

---

### How would you design an online collaborative editor (e.g. Google Docs)?

The central challenge here is managing concurrent edits from multiple users on the same document while ensuring consistency.

**Core Functional Requirements:**

* Multiple users can edit a document simultaneously.
* Changes made by one user are visible to others in real-time.
* The document should always converge to a consistent state.

**Non-Functional Requirements:**

* **Low Latency:** Edits should appear for other users very quickly.
* **Consistency:** All users must eventually see the same version of the document.

**High-Level Architecture:**

The architecture revolves around a centralized server that manages the state of the document and resolves conflicts.

* **Client:** The web-based editor. It maintains a local copy of the document and sends user-generated changes (operations) to the server.
* **Real-time Communication:** A persistent WebSocket connection is established between the client and the server for sending and receiving operations.
* **Document Service:** The backend service that manages the authoritative state of the document.
* **Conflict Resolution:** This is the most critical part. Two primary algorithms are used:
  * **Operational Transformation (OT):** This is the algorithm famously used by Google Docs. When a client sends an operation, the server transforms it against any concurrent operations it has already processed before applying it. The transformed operation is then broadcast to all other clients. This ensures that all clients eventually reach the same state.
  * **Conflict-free Replicated Data Types (CRDTs):** A newer approach where data structures are designed to be inherently conflict-free. Each client can apply changes locally and then sync with other clients, and the data type's properties guarantee eventual consistency.

**Data Storage:**

* **Document Content:** A database that can handle frequent updates and versioning is needed. Storing the document as a series of change operations (the edit history) is a common approach.
* **Snapshots:** Periodically, the server can create a snapshot of the document's current state to speed up loading times for new users joining the session.

---

### How would you design a typeahead feature (e.g. Google search autocomplete)?

The primary goal of a typeahead service is to provide instant, relevant suggestions as a user types. This requires a highly efficient data structure for prefix searching.

**Core Functional Requirements:**

* Return a list of top suggestions based on the user's input prefix.
* Suggestions should be ranked by relevance (e.g., popularity).

**Non-Functional Requirements:**

* **Extremely Low Latency:** Suggestions should appear in under 200ms.
* **Scalability:** Must handle a massive number of queries per second.

**High-Level Architecture:**

* **Data Structure: The Trie**
  * A **Trie** (prefix tree) is the ideal data structure for this problem. Each node in the trie represents a character. A path from the root to a node forms a prefix. We can store the top suggestions and their frequencies at each node that represents a valid prefix.
* **Offline Data Processing:**
  * The trie would be built offline using historical search query data. A MapReduce or Spark job would process query logs to calculate the frequency of each query.
  * This pre-computed trie is then loaded into memory on our serving machines.
* **Serving Layer:**
  * When a user types a character, a request is sent to the backend.
  * The backend traverses the in-memory trie to the node corresponding to the typed prefix.
  * It then retrieves the pre-computed list of top suggestions stored at that node and returns them to the client.

**Scalability and Optimization:**

* **Distributed Trie:** The trie can be sharded across multiple machines to handle a vast vocabulary.
* **Caching:** A caching layer (like Memcached or Redis) can be used to cache results for very common prefixes.
* **Personalization:** User-specific suggestions can be incorporated by merging results from a personalized trie with the global trie.

---

### How would you design Twitter's trending topics?

Trending topics are not just the most frequent hashtags. The algorithm needs to identify topics that are suddenly becoming popular.

**Core Functional Requirements:**

* Identify a list of topics (hashtags, keywords) that are currently trending.
* Rank these topics by their "trendiness."

**High-Level Architecture:**

This is a real-time data processing and analytics problem.

* **Data Ingestion:** A stream of all tweets is the input. This would likely be consumed from a message queue like Kafka.
* **Stream Processing:** A stream processing framework like Apache Flink or Spark Streaming would process the tweets in real-time.
* **Counting and Windowing:**
  * The system would count the occurrences of hashtags and keywords within short time windows (e.g., every few seconds or minutes).
  * To identify what's "trending," we need to look at the rate of increase. The algorithm would compare the counts in the current window to previous windows. A topic with a sharp increase in frequency is a strong candidate for a trending topic.
* **Distributed Counting:** To handle the massive volume of tweets, the counting would be distributed. Each processing node would handle a subset of the data, and the results would be aggregated.
* **Ranking:** After identifying potential trending topics, a ranking algorithm would be applied. This could factor in not just the velocity but also other signals like the number of unique users tweeting about the topic to prevent spam.
* **Serving:** The final ranked list of trending topics is stored in a fast-access data store (like Redis) and served to clients. This list is updated frequently.

**Personalization:**

Trending topics can be personalized based on a user's location, interests, and the people they follow. This would involve joining the user's profile information with the trending topics data during the serving phase.

---

### How would you design a distributed Botnet?

This is an interesting and unusual request. Designing a botnet from a purely technical standpoint involves creating a resilient and stealthy command and control (C2) infrastructure.

**Disclaimer:** This information is for educational purposes only. Creating and operating a botnet is illegal and harmful.

**Key Design Principles:**

* **Resilience:** The C2 infrastructure should be difficult to take down.
* **Stealth:** Communication between the bots and the C2 server should be hard to detect and trace.
* **Scalability:** The system should be able to manage a large number of bots.

**Command and Control (C2) Architectures:**

* **Centralized Model:** All bots communicate with a single C2 server. This is the simplest to implement but also the most vulnerable, as taking down the central server decapitates the botnet.
* **Peer-to-Peer (P2P) Model:** Bots communicate with each other, relaying commands and updates. This is much more resilient as there is no single point of failure. However, it can have higher latency.
* **Hybrid Model:** A combination of centralized and P2P models. For example, bots might be organized into clusters with a local C2, and these local C2s communicate in a P2P fashion or with a higher-level C2.

**Communication:**

* **Protocols:** Botnets can use standard protocols like HTTP or IRC for their C2 communication, often disguised as normal traffic. Some more sophisticated botnets use custom, encrypted protocols.
* **Encryption:** Asymmetric encryption is crucial for the botmaster to securely issue commands that cannot be forged.

**Bot Functionality:**

* **Infection Vector:** The mechanism by which the bot infects new machines.
* **Payload Delivery:** The ability to download and execute new code from the C2 server.
* **Command Execution:** The bot must be able to carry out commands, such as launching a DDoS attack or sending spam.

---

### How would you design a system that can handle millions of card transactions per hour?

This requires a system that is extremely secure, reliable, and highly scalable.

**Core Functional Requirements:**

* Process credit/debit card payments.
* Handle authorizations, captures, and refunds.
* Ensure the security of payment data.

**Non-Functional Requirements:**

* **High Throughput:** Handle a very large number of transactions per second.
* **Low Latency:** Transactions should be processed quickly.
* **High Availability:** Downtime can result in significant financial loss.
* **Security and Compliance:** Must be compliant with standards like PCI DSS.

**High-Level Architecture:**

A distributed, asynchronous, microservices-based architecture is essential.

* **API Gateway:** The entry point for payment requests from merchants.
* **Transaction Service:** The core service that orchestrates the payment flow.
* **Message Queue:** A message queue like Kafka is central to this design. When a payment request comes in, the Transaction Service puts a message on the queue. This decouples the initial request from the complex backend processing and provides durability.
* **Payment Processor Integration:** Worker services consume messages from the queue and communicate with external payment processors (like Visa, Mastercard) and acquiring banks.
* **Ledger Service:** A highly reliable service that maintains the financial ledger. This needs to be built on a database that supports ACID transactions.
* **Fraud Detection Service:** A service that analyzes transactions in real-time to detect and block fraudulent activity. This might involve machine learning models.

**Data Storage:**

* **Transactional Data:** A highly available and consistent database like a distributed SQL database (e.g., CockroachDB, Google's Spanner) is suitable for the ledger.
* **Security:** Sensitive cardholder data should be encrypted both in transit and at rest. Tokenization is a common technique where the actual card number is replaced with a non-sensitive token.

**Scalability and Resilience:**

* **Horizontal Scaling:** All services should be designed to be stateless so they can be scaled horizontally.
* **Redundancy:** Redundant connections to payment processors and data centers are crucial for high availability.

---

### How would you design security for Meta's corporate network from scratch?

Designing corporate network security for a company like Meta requires a multi-layered, defense-in-depth approach, often referred to as a "Zero Trust" model.

**Fundamental Principle: Zero Trust**

The core idea of Zero Trust is to "never trust, always verify." No user or device is trusted by default, regardless of whether they are inside or outside the corporate network.

**Key Design Pillars:**

1. **Identity and Access Management (IAM):**
    * **Strong Authentication:** Mandatory multi-factor authentication (MFA) for all users and services.
    * **Principle of Least Privilege:** Users and services are only granted the minimum level of access necessary to perform their functions.
    * **Centralized Identity Provider:** A single source of truth for user identities.

2. **Network Segmentation:**
    * The network should be divided into smaller, isolated segments. This limits the "blast radius" if one segment is compromised. For example, the engineering network would be separate from the finance network.
    * Firewalls and access control lists (ACLs) would strictly control traffic between segments.

3. **Endpoint Security:**
    * All corporate devices (laptops, servers) must have advanced endpoint detection and response (EDR) agents.
    * Strict device posture checks are enforced. A device that is not up-to-date with security patches or has unapproved software would not be allowed on the network.

4. **Data Protection:**
    * **Encryption:** All data should be encrypted at rest and in transit.
    * **Data Loss Prevention (DLP):** Systems would be in place to detect and prevent the unauthorized exfiltration of sensitive data.

5. **Threat Detection and Response:**
    * **Comprehensive Logging and Monitoring:** All network traffic, system logs, and access attempts are logged and sent to a central Security Information and Event Management (SIEM) system.
    * **Intrusion Detection/Prevention Systems (IDS/IPS):** To detect and block malicious network activity.
    * **Security Operations Center (SOC):** A team of security analysts who monitor for threats 24/7 and respond to incidents.

**Implementation Steps:**

1. **Asset Inventory:** Catalog all hardware, software, and data assets.
2. **Threat Modeling:** Identify potential threats and vulnerabilities.
3. **Architectural Design:** Design the network with segmentation and Zero Trust principles.
4. **Tool Selection and Implementation:** Deploy firewalls, IAM solutions, EDR, SIEM, etc.
5. **Policy and Procedure Development:** Define security policies and incident response plans.
6. **Continuous Monitoring and Improvement:** Security is an ongoing process of monitoring, testing, and adapting to new threats.

### Design a Service or Product API

"That's a great question. Designing a good API is crucial because it's the contract between the service and its consumers. A well-designed API is easy to understand, easy to use, and flexible enough to evolve. I'll walk through my design process for a product API for an e-commerce platform."

**1. Requirements and Use Cases (Clarifying Questions)**

"First, I'd want to clarify the primary goals. Let's assume the key use cases are:

* **Third-party merchants:** Need to manage their product catalog (create, read, update, delete - CRUD).
* **Internal front-end applications:** Need to display products to customers and search the catalog.
* **Data analytics team:** Needs to pull product data for analysis.

This tells me we need robust CRUD functionality, powerful query capabilities, and clear, consistent data models."

**2. API Design Philosophy: RESTful Principles**

"I would design this as a **RESTful API** over HTTP/S. It's a well-understood, standard approach that leverages existing HTTP methods and concepts.

* **Resources, not actions:** The API will be centered around the `Product` resource.
* **Standard HTTP Methods:** We'll use `GET` for retrieval, `POST` for creation, `PUT`/`PATCH` for updates, and `DELETE` for removal.
* **Statelessness:** Each request from a client will contain all the information needed to process it. The server won't store any client session state. This is critical for scalability.
* **JSON for Data Format:** We'll use JSON for both request bodies and response payloads as it's lightweight and universally supported."

**3. API Endpoints (The Contract)**

"Here are the core endpoints I would define for the `/products` resource:"

| Method   | Endpoint                   | Description                                                                |
| :------- | :------------------------- | :------------------------------------------------------------------------- |
| `GET`    | `/v1/products`             | Get a paginated list of all products. Would support filtering and sorting. |
| `POST`   | `/v1/products`             | Create a new product. The request body would contain the product details.  |
| `GET`    | `/v1/products/{productId}` | Retrieve a single product by its unique ID.                                |
| `PUT`    | `/v1/products/{productId}` | Fully update an existing product. Replaces the entire resource.            |
| `PATCH`  | `/v1/products/{productId}` | Partially update a product (e.g., just change the price).                  |
| `DELETE` | `/v1/products/{productId}` | Delete a product.                                                          |

**4. Data Model**

"A request to `POST /v1/products` or a response from `GET /v1/products/{productId}` would look something like this:"

```json
{
  "id": "prod_12345abc",
  "name": "Classic Blue T-Shirt",
  "description": "A comfortable, 100% cotton t-shirt.",
  "price": {
    "amount": 2500,
    "currency": "USD"
  },
  "sku": "SKU-BLUE-L",
  "inventory": {
    "quantity": 150,
    "status": "in_stock"
  },
  "created_at": "2025-07-14T10:00:00Z",
  "updated_at": "2025-07-14T10:00:00Z"
}
```

**5. Important Design Considerations**

* **Versioning:** Notice the `/v1/` in the endpoint. API versioning is non-negotiable. It allows us to introduce breaking changes in a future `v2` without disrupting existing clients. This version can be in the URL path, as a query parameter, or in a custom request header. I prefer the URL path as it's explicit.
* **Authentication & Authorization:** For a service like this, I'd use **OAuth 2.0**. Clients would get a bearer token from an authentication service and include it in the `Authorization` header. We'd also need authorization logic to ensure, for example, that a merchant can only modify their own products.
* **Filtering, Sorting, and Pagination:** For the `GET /v1/products` endpoint, we must support these features to avoid overwhelming the client (and our servers). For example: `GET /v1/products?limit=50&offset=100&sort_by=price&status=in_stock`.
* **Error Handling:** We need a consistent error response format. For example, a non-existent product `GET /v1/products/invalid_id` would return a `404 Not Found` status with a clear JSON error body: `{ "error": { "code": "resource_not_found", "message": "Product with ID 'invalid_id' does not exist." } }`.
* **Rate Limiting:** To protect the service from abuse and ensure fair usage, we'd implement rate limiting based on the client's API key or IP address.
* **Documentation:** Finally, I'd use a standard like the **OpenAPI Specification (formerly Swagger)** to document the API. This provides interactive documentation, client code generation, and a clear contract for all consumers.

---

### Design a Chat Service API

"Designing a chat service API is a fascinating challenge that blends standard RESTful practices for setup and management with real-time protocols for the core messaging experience. Here’s how I'd approach it."

**1. Core Functional Requirements**

* One-on-one and group messaging.
* Send/receive messages in real-time.
* Message history/retrieval.
* Show user presence (online/offline/typing).
* Read receipts (delivered, read).

**2. High-Level Architecture: A Hybrid Approach**

"A chat service cannot be purely RESTful due to the real-time requirement. A REST API is client-initiated (pull), but we need the server to push messages to clients instantly. Therefore, my design uses a hybrid approach:

* **REST API:** For managing state that doesn't change frequently. Examples include user profiles, conversation lists, creating new groups, and fetching message history.
* **WebSockets:** For the core real-time communication. A persistent, bidirectional WebSocket connection is established between the client and a real-time gateway service for sending and receiving live messages, presence updates, and read receipts."

**3. REST API Endpoints**

"These endpoints manage the 'state' of the chat service."

| Method | Endpoint                              | Description                                                             |
| :----- | :------------------------------------ | :---------------------------------------------------------------------- |
| `GET`  | `/v1/conversations`                   | Get a list of the current user's conversations (both 1-on-1 and group). |
| `POST` | `/v1/conversations`                   | Create a new conversation (e.g., a new group chat).                     |
| `GET`  | `/v1/conversations/{convId}/messages` | Get a paginated history of messages for a specific conversation.        |
| `POST` | `/v1/conversations/{convId}/messages` | Send a message (primarily for offline users or as a fallback).          |

**4. WebSocket Communication (The Real-time Layer)**

"Once the client is loaded, it would open a WebSocket connection to an endpoint like `wss://chat.api.service.com/v1/connect`. After connecting and authenticating (usually by sending a token as the first message), the client and server exchange JSON-formatted event payloads."

**Client-to-Server Events:**

* **Sending a message:**

    ```json
    {
      "event": "send_message",
      "payload": {
        "conversation_id": "conv_abc123",
        "text": "Hello world!"
      }
    }
    ```

* **Typing indicator:**

    ```json
    {
      "event": "typing_started",
      "payload": { "conversation_id": "conv_abc123" }
    }
    ```

* **Marking a message as read:**

    ```json
    {
      "event": "mark_as_read",
      "payload": { "last_read_message_id": "msg_xyz789" }
    }
    ```

**Server-to-Client Events:**

* **New message delivery:**

    ```json
    {
      "event": "new_message",
      "payload": {
        "id": "msg_def456",
        "conversation_id": "conv_abc123",
        "sender_id": "user_987",
        "text": "Hey there!",
        "timestamp": "2025-07-14T11:00:00Z"
      }
    }
    ```

* **Presence update:**

    ```json
    {
      "event": "presence_update",
      "payload": {
        "user_id": "user_123",
        "status": "online"
      }
    }
    ```

**5. System Design Considerations**

* **Scalability:** The real-time layer is the biggest challenge. We would need a horizontally scalable **WebSocket Gateway** service. A single user's connection would be handled by one server, but that server needs to communicate with other backend services. A Pub/Sub system (like Kafka or Redis Pub/Sub) is essential here. When User A sends a message, the gateway handling their connection publishes it to a topic for that conversation. Gateways connected to other users in that conversation subscribe to the topic and push the message to their respective clients.
* **Persistence:** Messages must be stored durably. I'd use a scalable NoSQL database like Cassandra or Bigtable, optimized for time-series data, using the `conversation_id` as the partition key and a timestamp as the clustering key for efficient queries.
* **Offline Handling:** If a user is offline, messages sent to them are persisted in the database. When they reconnect, the client can use the REST endpoint (`GET /v1/conversations/{convId}/messages`) to fetch any messages they missed since their last known sync time. For a better user experience, the server could also send push notifications for offline messages.

---

### Design an Email Server

"Designing an email server is a classic system design question that involves understanding well-established internet protocols. It's really about designing a distributed system for reliable message intake, routing, and delivery. I'll break it down into the core components and protocols."

**1. Core Components**

"An email system isn't a single application but a collection of services working together. The two most critical components are:

1. **Mail Transfer Agent (MTA):** This is the 'post office' of the email world. Its job is to receive email from other MTAs (or from a user's client) and route it toward its destination. It doesn't deal with mailboxes directly. Popular MTA software includes Postfix and Exim.
2. **Mail Delivery Agent (MDA):** Once an MTA has determined that an email belongs to a local user on its server, it hands the email to the MDA. The MDA is responsible for placing the email into the correct user's mailbox. It can also perform filtering, such as for spam or routing to specific folders."

**2. Key Protocols**

"The entire system is built on a foundation of standard protocols:

* **SMTP (Simple Mail Transfer Protocol):** Used for **sending** email. When you send an email, your client speaks SMTP to your outgoing mail server (an MTA). MTAs also speak SMTP to each other to transfer the email across the internet. It typically runs on port 25 for server-to-server communication and port 587 for client submissions.
* **IMAP (Internet Message Access Protocol):** Used for **retrieving and managing** email. IMAP is the modern standard. It allows the client to sync with the server, keeping a consistent state of read/unread messages and folder structures across multiple devices (phone, laptop, etc.). The emails stay on the server.
* **POP3 (Post Office Protocol 3):** An older protocol for **retrieving** email. It's simpler: it typically downloads emails from the server to the client and then deletes them from the server. It's less common now because it doesn't support synchronization across multiple devices."

**3. High-Level Architecture for Sending and Receiving**

"Let's trace the path of an email from `alice@google.com` to `bob@example.com`."

**Sending Flow (Alice's side):**

1. Alice's email client (e.g., Gmail on her phone) connects to Google's outgoing MTA (e.g., `smtp.google.com`) using SMTP.
2. Google's MTA receives the email. It looks at the recipient domain (`example.com`).
3. The MTA performs a **DNS MX (Mail Exchange) record lookup** for `example.com` to find the IP address of the MTA responsible for handling mail for that domain (e.g., `mx.example.com`).
4. Google's MTA opens an SMTP connection to `mx.example.com` and transfers the email.

**Receiving Flow (Bob's side):**
5.  The `mx.example.com` MTA receives the email. It sees that the recipient, `bob`, is a local user.
6.  The MTA hands the email off to the local **Mail Delivery Agent (MDA)**.
7.  The MDA might first pass the email through a **Spam and Virus Filter**. If it passes, the MDA places the email into Bob's mailbox file on the server.
8.  Later, Bob opens his email client. The client uses **IMAP** to connect to `example.com`'s mail server, authenticates, and syncs, downloading a copy of the new email from Alice.

**4. Design Considerations for a Large-Scale Service**

* **Scalability & Availability:**
  * **MTA Fleet:** We wouldn't have one MTA server but a large, load-balanced fleet of them.
  * **Mailbox Storage:** User mailboxes can't be stored on a single machine's filesystem. We'd use a distributed storage system (like Google's own Spanner or a custom solution built on Bigtable) to store emails and metadata. This provides redundancy and horizontal scalability. The storage would be sharded by user ID.
  * **DNS Redundancy:** We'd have multiple MX records with different priorities for our domain to ensure that if one MTA fleet is down, sender MTAs can try the next one.
* **Spam and Phishing Filtering:** This is a massive machine learning problem. A dedicated filtering service would analyze incoming emails based on sender reputation, content, headers, and other signals to quarantine or reject spam. This service needs to be updated constantly to fight new attack vectors.
* **Security:**
  * **Encryption in Transit:** Use **TLS** for all SMTP, IMAP, and POP3 connections to prevent eavesdropping.
  * **Authentication:** Implement strong authentication for users connecting via IMAP/POP3.
  * **Sender Authentication:** Implement standards like **SPF, DKIM, and DMARC** to help prevent email spoofing and phishing. These are DNS-based mechanisms that allow receiving MTAs to verify that an email claiming to be from a certain domain was actually sent by an authorized server.
